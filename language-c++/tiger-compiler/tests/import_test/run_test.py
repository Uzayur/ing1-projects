from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../src/tc bad_import.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc fortytwo-main-good-import.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc import-rec.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc import-itself.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
