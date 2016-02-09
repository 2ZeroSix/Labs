def testcalc():
    from subprocess import Popen, TimeoutExpired
    import os
    import argparse
    class Test_Error(Exception): pass
    class Can_not_find_file(Exception): pass
    class Can_not_find_tests(Exception): pass
    def getout(prog_name):
        try:
            if not os.path.isfile(prog_name): raise Can_not_find_file
            file = Popen([prog_name], stdin=open('test/in.txt', 'r'), stdout=open('test/out.txt', 'w'), shell=True)
            file.wait(timeout=3)
            return True
        except TimeoutExpired:
            return False
    try:
        testin = []
        testout = []
        if not os.path.isfile("test/tests.txt"): raise Can_not_find_tests
        file_with_tests = open("test/tests.txt", "r")
        test_line = file_with_tests.readline()
        while (test_line):
            testin.append(test_line[:test_line.find('|')])
            testout.append(test_line[test_line.find('|') + 1: -1])
            test_line = file_with_tests.readline()
        file_with_tests.close()
        testfilename = input("filename: ")
        i=0
        while(i<len(testin)):
            infl=open('test/in.txt', 'w')
            infl.write(testin[i])
            infl.close()
            if(getout(testfilename)):
                outfl=open('test/out.txt', 'r')
                outtxt=outfl.readline()
                outfl.close()
                if(outtxt == testout[i]):
                    print("test ",str(i+1),'/',str(len(testout)),": passed")
                    i+=1
                else:
                    print("test ",str(i+1)+'/'+str(len(testout)),": wrong output")
                    raise Test_Error
            else:
                print("test",str(i),"timeout")
                raise Test_Error
        else:
            input("Complete")
    except Test_Error:
        input("ERROR")
    except Can_not_find_file:
        input("can't find")
    except Can_not_find_tests:
        input("can't find file with tests\nmake file 'test\\tests.txt'\nformat :\n<input_text1>|<output_text1>\n<input_text2>|<output_text2>")

testcalc()
