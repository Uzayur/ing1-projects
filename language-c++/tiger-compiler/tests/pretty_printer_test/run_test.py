from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        subprocess.run("../../src/tc -o -A simple_print.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_let.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_hexa.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_for.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_weird.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A cross_functions.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_or.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_and.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_let_type.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A methods_dec.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A multiple_args_function.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A methods_dec.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_array_dec.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_array_for.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_array.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A  test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_attribut.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A  test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_class.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A  test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_for.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A  test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_prints.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_string.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_type.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A triple_print.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A simple_prints.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A while_functions.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        subprocess.run("../../src/tc -o -A zero.tig >> test1", stdout=PIPE, shell=True)
        subprocess.run("../../src/tc -o -A test1 >> test2", stdout=PIPE, shell=True)
        exit1 = subprocess.run("diff test1 test2; echo $?;", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0; rm test1 test2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
