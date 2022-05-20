#!/usr/bin/python3

import sys, shutil, os

def main():

   pre = '../..'
   directory = '../Source'
   for x in os.walk(directory):
      print(pre + x[0][2:])



if __name__ == '__main__':
   main()
