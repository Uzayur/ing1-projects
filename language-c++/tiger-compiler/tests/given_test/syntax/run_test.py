from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../../src/tc -X --parse typeid.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
