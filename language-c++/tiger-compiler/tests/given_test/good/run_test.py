from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../../src/tc -o -bBT array-of-alias.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT array.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT break-in-while.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT comments-nested.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT compare-record-and-nil.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT fact.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT for-in-let.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT fun-vs-var.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT if.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT local-vs-global-type.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT mutually-recursive-functions.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT mutually-recursive-procedures.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT queens.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT record.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT recursive-types.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT shadowing-functions.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT shadowing-types-separate.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test27.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test30.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test37.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test42.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test44.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT test64.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT three-name-spaces.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../../src/tc -o -bBT merge.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
