# import os
# import sys
# os.system('python3 -m pip install -r requirements.txt')
import subprocess
import sys
process = subprocess.Popen(
    ['python3', '-m', 'pip', 'install', '-r', 'requirements.txt'], stdout=subprocess.PIPE)
output, error = process.communicate()
output = output.decode("utf-8").split('\n')
print(output,error)
