from subprocess import Popen, PIPE
from os import listdir
from os.path import isfile, join
from filecmp import cmp
import time

FILENAME = './Snir1.exe'

error_files = [f for f in listdir('error_tests') if isfile(join('error_tests', f))]
errot_tests = [f for f in error_files if f.startswith("test_")]

tests = [f for f in listdir('Tests') if isfile(join('Tests', f))]
tests = [f for f in tests if f.endswith(".in")]

for test in errot_tests:
    p = Popen([FILENAME, join('error_tests',test), 'b'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    time.sleep(0.1)
    output_file = join('error_tests',test.replace('test','output'))
    with open("b") as f1:
        with open(output_file) as f2:
            str1 = f1.read()
            str2 = f2.read()
            if str1 != str2:
                print("test - %s\noutput - %s\n" % (test, output_file))
                print(str1 + "\n\n" + str2)
                raise Exception("")

for test in tests:
    p = Popen([FILENAME, join('Tests',test), 'b'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    time.sleep(0.1)
    output_file = join('Tests',test.replace('.in','.out'))
    with open("b") as f1:
        with open(output_file) as f2:
            str1 = f1.read()
            str2 = f2.read()
            if str1 != str2:
                print("test - %s\noutput - %s\n" % (test, output_file))
                print(str1 + "\n\n" + str2)
                raise Exception("")


p = Popen([FILENAME, join('error_tests',"not_exist"), 'b'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
time.sleep(0.1)
out, err = p.communicate()
with open("b") as f1:
    print("It's OK. when file doesn't exist the Error message is- ")
    print(err)