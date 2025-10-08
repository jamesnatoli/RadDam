import ROOT
import json
import shutil
import os
from tqdm import tqdm

input_file = "/eos/user/n/naislam/HF_Raddam_2/2024/2024I/Untuplizer/trig_added/output_data_2024I.root"
output_file = input_file.replace(".root", "_withSF.root")
json_file = "/eos/user/n/naislam/HF_Raddam_2/2024/2024I/Untuplizer/trig_added/electronHlt.json"

print("Copying ROOT file...")
if not os.path.exists(output_file):
    shutil.copy(input_file, output_file)
    print(f"Copied to: {output_file}")
else:
    print(f"Output file already exists: {output_file}, will be updated.")

print("Loading scale factors from JSON...")
with open(json_file) as f:
    sf_json = json.load(f)

corr = next(c for c in sf_json["corrections"] if c["name"] == "Electron-HLT-SF")
sf_data = corr["data"]["content"]
year_entry = next(i for i in sf_data if i["key"] == "2023PromptC")
valtype_entry = next(i for i in year_entry["value"]["content"] if i["key"] == "sf")
path_entry = next(i for i in valtype_entry["value"]["content"] if i["key"] == "HLT_SF_Ele30_TightID")

edges_eta = path_entry["value"]["edges"][0]
edges_pt = path_entry["value"]["edges"][1]
sf_values = path_entry["value"]["content"]
sf_array = [sf_values[i:i + len(edges_pt) - 1] for i in range(0, len(sf_values), len(edges_pt) - 1)]

def get_sf(eta, pt):
    eta_bin = next((i for i in range(len(edges_eta) - 1) if edges_eta[i] <= eta < edges_eta[i+1]), len(edges_eta) - 2)
    pt_bin = next((j for j in range(len(edges_pt) - 1) if edges_pt[j] <= pt < edges_pt[j+1]), len(edges_pt) - 2)
    return sf_array[eta_bin][pt_bin]

print("Opening ROOT file with PyROOT...")
ROOT.gROOT.SetBatch(True)
f = ROOT.TFile(output_file, "UPDATE")
tree = f.Get("miniTree")

n_entries = tree.GetEntries()
print("Total entries:", n_entries)

eleHLTSF = ROOT.std.vector('float')()
branch_hlt_sf = tree.Branch("eleHLTSF", eleHLTSF)

print("Processing entries...")
for i in tqdm(range(n_entries)):
    tree.GetEntry(i)

    eleHLTSF.clear()

    pts = getattr(tree, "ele_pt")
    etas = getattr(tree, "ele_eta")
    trig = getattr(tree, "HLT_Ele30WPTightGsf")

    if trig:
        for pt, eta in zip(pts, etas):
            sf = get_sf(eta, pt)
            eleHLTSF.push_back(sf)
    else:
        for _ in range(len(pts)):
            eleHLTSF.push_back(1.0)

    branch_hlt_sf.Fill()

print("Writing new branch to file...")
tree.Write("", ROOT.TObject.kOverwrite)
f.Close()
print("Done.")
