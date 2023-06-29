from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../../src/tc -o -bB break-outside-loop.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB invalid-function-redefinition-1.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB invalid-type-redefinition.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB test17.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB test18.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB test19.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB undeclared-variable.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bB unknown-record.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
