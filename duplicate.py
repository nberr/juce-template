#!/usr/bin/python3

import sys, shutil, os, datetime

VERSION = "1.0"

def main():
    global VERSION
    print(f'juce-template duplicator v{VERSION} by nberr')

    numargs = len(sys.argv) - 1

    if not (numargs == 3):
        print('Usage: python duplicate.py plugin_name plugin_prefix author')
        sys.exit(1)
    else:
        plugin_name = sys.argv[1]
        plugin_prefix = sys.argv[2]
        plugin_author = sys.argv[3]

    src = os.path.dirname(os.path.realpath(__file__))
    src = f'{src}/PluginName'

    dest = os.path.dirname(os.path.realpath(__file__))
    dest = f'{dest}/{plugin_name}'

    # copy the directory
    shutil.copytree(src, dest)

    # rename the files
    # jucer file
    os.rename(f'{dest}/PluginName.jucer', f'{dest}/{plugin_name}.jucer')


    # .jucer internals
    with open (f'{dest}/{plugin_name}.jucer', 'r') as jucer:
        jucerdata = jucer.read()

    jucerdata = jucerdata.replace('PluginName', plugin_name)

    with open (f'{dest}/{plugin_name}.jucer', 'w') as jucer:
        jucer.write(jucerdata)

    # files in Source folder
    for sourcefile in os.listdir(f'{dest}/Source'):
        if sourcefile.startswith('PluginName'):
            renamedfile = sourcefile.replace('PluginName', plugin_name)
            os.rename(f'{dest}/Source/{sourcefile}', f'{dest}/Source/{renamedfile}')

    # source file internals
    for root, dirs, files in os.walk(f'{dest}/Source'):
        for file in files:
            filepath = os.path.join(root, file)
            with open(filepath, 'r') as cursource:
                filedata = cursource.read()
            filedata = filedata.replace('PluginName', plugin_name)
            filedata = filedata.replace('PNP', plugin_prefix)
            filedata = filedata.replace('Nicholas Berriochoa', plugin_author)

            curr_date = datetime.datetime.now()
            for line in filedata.split('\n'):
                if "Created: " in line:
                    filedata = filedata.replace(line.strip(), f'Created: {curr_date.strftime("%d %b %Y %I:%M:%S%p")}')

            with open(filepath, 'w') as cursource:
                cursource.write(filedata)



if __name__ == '__main__':
    main()
