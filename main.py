import os
import sys
import time

argc = len(sys.argv)
argv = sys.argv

if argc > 2:
   cmd = './'
   start = time.time()
   for i in range(1, argc):
      cmd = cmd + argv[i] + ' '
   if os.path.isfile(argv[1]):
      os.system(cmd)
      print(time.time() - start)
   else:
      print('Did not find binary file here:')
      print(os.listdir('.'))
else:
   print('python', argv[0], 'path_to_binary_file path_to_image [save_path]')
   print('e.g. python main.py cmake-build/AAMED images/1.jpg')
   exit(0)