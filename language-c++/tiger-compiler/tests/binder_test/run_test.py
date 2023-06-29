from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        subprocess.run("../../src/tc -o -bBA simple_let.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -bBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -bBA simple_call_exp.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -bBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -bBA simple_undeclared.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -bBA simple_redefinitions.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -XbBA simple_while_for.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -XbBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -bBA simple_break_outside.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -bBA simple_tydec.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -bBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -bBA simple_type_error.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -bBA simple_class.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -bBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -bBA simple_class_error.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 4; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -bBA self.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -bBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -bBA simple_class_method.tig >> test1", stdout=PIPE, shell=True)
        exit1 = subprocess.run("../../src/tc -o -bBA test1 >> test2; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
