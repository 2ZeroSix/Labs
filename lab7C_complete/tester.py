from subprocess import *
import os
class Test_Error(Exception): pass
class Can_not_find_file(Exception):pass

def getout(prog_name):
        try:
                cmd = prog_name
                file = Popen([prog_name], stdin=open('test/in.txt', 'r'), stdout=open('test/out.txt', 'w'), shell=True)
                file.wait(timeout=3)
                return True
        except TimeoutExpired:
                return False
try:
        testin = []
        testout = []
        file_with_tests = open("test/tests.txt", "r")
        test_line = file_with_tests.readline()
        i=0
        while (test_line):
                testin.append(test_line[:test_line.find('|')])
                testout.append(test_line[test_line.find('|') + 1: -1])
                test_line = file_with_tests.readline()
                i+=1
        file_with_tests.close()
        testfilename = input("введите имя файла: ")
        if not os.path.isfile(testfilename): raise Can_not_find_file
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
                input("Все тесты пройдены")
except Test_Error:
        input("Конец тестирования, встречена ошибка\nпоследняя информация в папке test")
except Can_not_find_file:
        input("Файл не найден")
