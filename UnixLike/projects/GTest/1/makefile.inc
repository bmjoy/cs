##########################################################################
## ģ�����ƣ�ϵͳ�������
## �ļ����ƣ�makefile
## ��    �ߣ������
## �������ڣ�2013-07-15 10:21:00
## �޸ļ�¼:
##
##########################################################################
#Ŀ���ļ���
OBJS = add.$(TO)\
       AddUnitTest.$(TO)\

all: cleanobj $(EXES)

add.$(TO):add.cpp
	$(CC) $(CFLAGS) add.cpp $(INCDIR)
 AddUnitTest.$(TO): AddUnitTest.cpp
	$(CC) $(CFLAGS) AddUnitTest.cpp $(INCDIR)

$(EXES): $(OBJS)
	$(LD) $(LFLAGS) -o$(OUTDIR)/$(EXES) $(OBJS) $(STDLIBS) $(DEFLIBS) $(EXPS)

#(3)��������
cleanobj:
	$(RM) -rf *.$(TO) *.gcda *.gcno AddUnitTest cov_report* core*
clean:cleanobj
	@echo clean all