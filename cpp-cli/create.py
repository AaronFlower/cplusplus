# encoding:utf-8

import sys
import os

def create():
    project_name = str(sys.argv[1])
    gtest_path = os.environ.get("GTEST_PATH", None);

    if gtest_path is None:
        print("[-] Error: can't find googletest path(GTEST_PATH  variable)")
        return

    if (not os.path.isdir(gtest_path)):
        print("[-] Error: googletest GTEST_PATH is not a valid directory")
        return

    if (os.path.isdir(project_name)):
        print("[-] Error: the project folder has been created")
        return

    createFolder(project_name, gtest_path)
    print("[+] Successfully created a cpp project.");
    return

def createFolder(root, gtest_path):
    assert isinstance(root, str) and len(root) > 0
    assert isinstance(gtest_path, str) and len(gtest_path) > 0
    os.makedirs(root)
    os.makedirs(root + "/build");
    os.makedirs(root + "/lib");
    # 注意: realpath 与 relpath 的区别.
    # os.symlink(os.path.relpath(gtest_path), root + "/lib/googletest", True)
    os.symlink(os.path.realpath(gtest_path), root + "/lib/googletest", True)
    return

if __name__ == "__main__":
    create()
