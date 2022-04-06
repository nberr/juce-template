#!/usr/bin/python3

import sys, shutil, os

def main():
    numargs = len(sys.argv) - 1
    
    if not (numargs == 1):
        print('Usage: python generate.py panel_name')
        sys.exit(1)
    else:
        panel_name = sys.argv[1]
        
    src = os.path.dirname(os.path.realpath(__file__))
    src = f'{src}/PanelTemplate'
    
    dest = os.path.dirname(os.path.realpath(__file__))
    dest = f'{dest}/{panel_name}'
    
    # copy the directory
    shutil.copytree(src, dest)
    
    # rename the files
    os.rename(f'{dest}/PanelName.cpp', f'{dest}/{panel_name}.cpp');
    os.rename(f'{dest}/PanelName.h', f'{dest}/{panel_name}.h');
    
    # rename file internals
    for sourceFile in os.listdir(dest):
        with open(f'{dest}/{sourceFile}', 'r') as cursource:
            filedata = cursource.read()
            
        filedata = filedata.replace('PanelName', panel_name)
            
        with open(f'{dest}/{sourceFile}', 'w') as cursource:
            cursource.write(filedata)

if __name__ == '__main__':
    main()
