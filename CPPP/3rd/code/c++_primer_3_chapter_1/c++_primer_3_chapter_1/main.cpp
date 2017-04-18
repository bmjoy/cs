#include <fstream>
#include <iostream>
#include <string>
int main()
{
    // std::ofstream outfile("hello_world.txt"); // �����ģʽ��
    // �ɲ������������⣬�������䶨����һ����������һ���ļ����������������з���
    // �������Լ�����ļ���д�����outfile << word����˼�ǣ�outfile�����Լ��ĺ���operator <<���Լ�д�����
    // ����Ӧ�ÿ����Ǹ������͵ģ�std::string, int,Ӧ�ö����ԣ�ֻ��������std::ofstream�������˺���operator <<��
    // ��չ��std::cout << "I love china"�����⣬std::coutӦ����һ�������ﶨ���һ��ȫ�ֵ�iostream����˵����
    // ������ʲô�ط���������һ�����壬std::ostream cout(),���������һ����׼���������˵���ˣ���һ�ֶ�̬�Ļ���
    // ��һ������̨�Ĵ��ڹ����������std::cout����std::cout << "I love china"һ��ִ�У������������̨���ڣ�
    // ˵����Ҳ���������׼���������д��������һ��char*�ַ�������iostream��Ҳһ��Ϊ����opreator << ������n������غ�����
    std::ofstream outfile("hello_world.txt", std::ios_base::app); // �Ը���ģʽ��

    // �������infile.txt�����ھͻᱨ�����ɲ������������⣬std::cin��������ǿ����Զ�������һ������̨���ڵģ��������һ��
    // ���ڣ��������ļ���������������ļ������ڣ����Ǿ͸����޷���ȡ���ݵġ�����ô���⵽���λ�ñȽ�ǣǿ�����ã���ʱ�����о�
    std::ifstream infile("infile.txt"); // ��infile.txt�����ݸ��ӵ�hello_world.txt�У�infile.txt�����Ѿ����򿪣��ļ�������
    if (!infile)                        // �ᱨ��
    {
        std::cerr << "error: unable to open input file!\n";
        return -1;
    }
    if (!outfile)
    {
        std::cerr << "error: unable to open output file!\n";
        return -2;
    }
    std::string word;
    while (infile >> word)
    {
        outfile << word << ' ';
    }
    return 0;
}