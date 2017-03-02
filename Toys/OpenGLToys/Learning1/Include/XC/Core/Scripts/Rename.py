import os


def rename_file(dire):
    path = os.path.split(dire)[0]
    filename = os.path.split(dire)[1]
    need_rename = False
    if filename[0] == 'X' and filename[1] == 'C':
        need_rename = True
    if not need_rename:
        print("'" + filename + "' do not need rename")
    else:
        print("'" + filename + "' need rename")
        new_name = filename[2:]
        print(new_name + " is new name")
        new_dir = path + "\\" + new_name
        print("new dir: " + new_dir)
        os.rename(dire, new_dir)
        print("rename finished")
    pass


def rename(path):
    files = os.listdir(path)
    for file in files:
        dire = os.path.join(path, file)
        if os.path.isdir(dire):
            rename(dire)
        else:
            rename_file(dire)
    pass


def main():
    path = os.path.dirname(os.getcwd())
    rename(path)
    pass


main()
