from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../../src/tc -o -bBT assign-loop-var.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT field-in-not-record.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT funarg-type-mismatch.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT missing-arg.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT nil-equal-nil.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test09.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test10.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test11.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test13.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test14.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test15.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test21.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test22.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test23.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test24.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test26.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test28.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test29.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test31.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test32.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test40.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test43.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT too-many-args.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT types-endless-recursion.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT unconstrained-nil.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
