#include "OtherLanguages/c/logsys/logsys.h"



int main()
{
	int iz = 0;
	int i = 0;
	CREATE_LOG(iz, "ׯ����")
	LOG_ERROR(iz, "һ�� ���Գ���� ȴԽ��Խ�ѹ�.%d", i++)
	LOG_ERROR(iz, "��ŵ ����˵����.%d", i++)
	LOG_ERROR(iz, "��Ĭ ��ʱ��͵��.%d", i++)
	LOG_ERROR(iz, "���� ����������.%d", i++)

	int ic = 0;
	CREATE_LOG(ic, "����Ѹ")
	LOG_ERROR(ic, "�����Ҳ�����.", i++)
	LOG_ERROR(ic, "��᲻�������������ķ�Χ.", i++)
	LOG_ERROR(ic, "һ����ʧ��  .", i++)
	LOG_ERROR(ic, "ȫ����ʧ�� .", i++)


	LOG_PLUSH(iz)
	LOG_PLUSH(ic)


	CREATE_LOG(LOG_SOCKET_IO_ID, LOG_SOCKET_IO_STR)
	LOG_ERROR(LOG_SOCKET_IO_ID, "������%d��%s��������.", 1, "��")
	LOG_PLUSH(LOG_SOCKET_IO_ID)
	getchar();
	return 0;
}