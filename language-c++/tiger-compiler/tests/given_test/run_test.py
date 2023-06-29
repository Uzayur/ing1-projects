from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("cd bind; python3 run_test.py; echo $?; cd ../", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0;", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("cd good; python3 run_test.py; echo $?; cd ../", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0;", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("cd syntax; python3 run_test.py; echo $?; cd ../", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0;", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("cd type; python3 run_test.py; echo $?; cd ../", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0;", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
