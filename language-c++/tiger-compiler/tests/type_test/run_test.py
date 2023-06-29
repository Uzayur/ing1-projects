from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../src/tc -T bad_add.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_add.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_compare.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_compare.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_while.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_while.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_test_while.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_assign.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_assign.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T multiples_vardec.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_multiples_vardec.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_fundec.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_return_fundec.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_for.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_for_index.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_for_return.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_args_call_exp.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_args_less.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_args_type.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T simple_call_exp.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_for_vardec.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_for_limit.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T bad_vardec_namety.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 5; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T and.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -T or.tig >> test1; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
