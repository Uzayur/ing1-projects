from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../src/tc --rename -A simple_multiple_definition.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc --rename -A primitive_test.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
