import gdown
import pathlib
import py7zr
import shutil

gdown.download(id="1tNIfm81yBp7DU3qfQVLLnewYwKlyzsrt", output="data.7z")
with py7zr.SevenZipFile("data.7z", mode="r") as z:
    z.extractall()
shutil.move("subset_sum", "data")
pathlib.Path("data.7z").unlink()
