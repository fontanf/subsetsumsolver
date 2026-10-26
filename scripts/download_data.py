import gdown
import pathlib
import py7zr
import shutil

gdown.download(id="1tNIfm81yBp7DU3qfQVLLnewYwKlyzsrt", output="data.7z")
with py7zr.SevenZipFile("data.7z", mode="r") as z:
    z.extractall()
# Move the datasets into 'data', which also contains the test instances.
data_path = pathlib.Path("data")
data_path.mkdir(exist_ok=True)
for dataset_path in pathlib.Path("subset_sum").iterdir():
    destination_path = data_path / dataset_path.name
    if destination_path.exists():
        shutil.rmtree(destination_path)
    shutil.move(str(dataset_path), str(destination_path))
pathlib.Path("subset_sum").rmdir()
pathlib.Path("data.7z").unlink()
