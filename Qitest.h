#include <iostream>
#include <vector>
#define TESTCASE_NAME(testcase_name) \
	testcase_name##_TEST

#define NANCY_TEST_(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase \
{ \
public: \
	TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase(case_name){}; \
	virtual void Run(); \
private: \
	static TestCase* const testcase_; \
}; \
	\
	TestCase* const TESTCASE_NAME(testcase_name) \
	::testcase_ = UnitTest::GetInstance()->RegisterTestCase(\
	new TESTCASE_NAME(testcase_name)(#testcase_name)); \
	void TESTCASE_NAME(testcase_name)::Run()

#define NTEST(testcase_name) \
	NANCY_TEST_(testcase_name)

#define RUN_ALL_TESTS() \
	UnitTest::GetInstance()->Run();

#define EXPECT_EQ(m, n) \
if (m != n) \
	{ \
	UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0; \
	std::cout << "Failed" << std::endl; \
	std::cout << "Expect:" << m << std::endl; \
	std::cout << "Actual:" << n << std::endl; \
	}


using namespace std;
class TestCase
{
public:
	TestCase(const char* case_name) : testcase_name(case_name){}

	// ִ�в��԰����ķ���
	virtual void Run() = 0;

	int nTestResult; // ���԰�����ִ�н�� 
	const char* testcase_name; // ���԰�������
};

class UnitTest
{
public:
	// ��ȡ����
	static UnitTest* GetInstance();

	// ע����԰���
	TestCase* RegisterTestCase(TestCase* testcase);

	// ִ�е�Ԫ����
	int Run();

	TestCase* CurrentTestCase; // ��¼��ǰִ�еĲ��԰���
	int nTestResult; // �ܵ�ִ�н��
	int nPassed; // ͨ��������
	int nFailed; // ʧ�ܰ�����
protected:
	std::vector<TestCase*> testcases_; // ��������
};


UnitTest* UnitTest::GetInstance()
{
	static UnitTest instance;
	return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
	testcases_.push_back(testcase);
	return testcase;
}

int UnitTest::Run()
{
	nTestResult = 1;
	for (std::vector<TestCase*>::iterator it = testcases_.begin();
		it != testcases_.end(); ++it)
	{
		TestCase* testcase = *it;
		CurrentTestCase = testcase;
		std::cout << "======================================" << std::endl;
		std::cout << "Run TestCase:" << testcase->testcase_name << std::endl;
		testcase->Run();
		std::cout << "End TestCase:" << testcase->testcase_name << std::endl;
		if (testcase->nTestResult)
		{
			nPassed++;
		}
		else
		{
			nFailed++;
			nTestResult = 0;
		}
	}

	std::cout  << "======================================" << std::endl;
	std::cout  << "Total TestCase : " << nPassed + nFailed << std::endl;
	std::cout  << "Passed : " << nPassed << std::endl;
	std::cout  << "Failed : " << nFailed << std::endl;
	return nTestResult;
}