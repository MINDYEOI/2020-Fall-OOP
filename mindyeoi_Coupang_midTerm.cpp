#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
using Matrix = vector<vector<string>>;




// ����1: �� �Լ����� ������ å��. �Լ��� ��Ȯ�� ����� ��쿡 10��, �׷��� ������ 0�� 
// ����2: �α��ν� �������� ID: admin, ��й�ȣ :0000 
// �䱸����1: ÷�ε� ��������(MidtermProjectCoupang.exe)�� ���۽��� ������ ������ ����ǵ��� �ڵ��� ��
// �䱸����2: file�� ������ �߰�/�����Ǵ���(������� ȸ�� �߰�) �Ϲ������� ������ �� �ֵ��� �ڵ��� �� (���� ������ ���Ͽ� ���ؼ��� �����ϸ� ���� �Լ� ��� ����)
// �䱸����3: (�ּ��� �����ϰ�) �Ʒ� �̹� �ۼ����ڵ带 �����Ͻ� ����, �� �ڵ带 Ȱ���ؼ� �ۼ��� ��
// �䱸����4: �Ʒ��� define�� symol�� ����Ͽ� �������� ���� ��(���� ���, info_client[0] ��� info_client[CLIENT_ID]�� ���, info_item[1] ��� info_client[ITEM_NAME]�� ���)
#define CLIENT_ID 0
#define CLIENT_PW 1
#define CLIENT_REGION 2
#define CLIENT_ORDER_LIST 3

#define ITEM_ID 0
#define ITEM_NAME 1
#define ITEM_PRICE 2
#define ITEM_QUANTITY 3


void admin_start(Matrix& info_client, Matrix& info_item);
void get_id_pw(string& id, string& pw);
string get_command_admin();
void client_start(Matrix& info_client, Matrix& info_item); // �߰����� (�ִ� 15��)

void read_info(Matrix& info_client, Matrix& info_item, string filename_client, string filename_item);  //10��
void write_info(const Matrix& info_client, const Matrix& info_item, string filename_client, string filename_item); //10��

void print_all(const Matrix& info_client); //10��
void print_each(const Matrix& info_client, int index); //10��
int search_client_by_id(const Matrix& info_client, string& id); //10��
void add_client(Matrix& info_client); //10��
void delete_client(Matrix& info_client);// 10��

vector<string> extract_regions(const Matrix& info_client); //10��
void print_items_by_region(const Matrix& info_client, const Matrix& info_item); // 10��
int search_item_by_id(const Matrix& info_item, string& id); // 10��
void add_item(Matrix& info_item); //10��
void delete_item(Matrix& info_item); //10��

/***************** CLIENT *****************/
string get_command_client();
int id_exists(Matrix& info_client, string& id);
bool pw_exists(Matrix& info_client, string& password);
void create_account(Matrix& info_client);
void sign_in(Matrix& info_client, Matrix& info_item);
void item_exists(Matrix& info_client, Matrix& info_item, string& item_id, int& client_id);
void shopping(Matrix& info_client, Matrix& info_item, int& client_id);
void printMe(const Matrix& info_client, int& client_id);
void editMe(Matrix& info_client, int& client_id);
bool leave(Matrix& info_client, int& client_id);
string get_command_myCoupang();
void MyCoupang(Matrix& info_client, Matrix& info_item, int& client_id);



int main() {
	string command;
	Matrix info_client(4), info_item(4); //info_client�� ȸ������, info_item�� ��ǰ������ ����
	read_info(info_client, info_item, "clients.txt", "items.txt");


	while (true) {
		cout << "1. ������ �α���" << endl;
		cout << "2. ȸ�� �α���" << endl;
		cout << "0. ���� �� ����" << endl;
		cout << ">>";
		cin >> command;
		if (command == "1")
			admin_start(info_client, info_item);
		else if (command == "2")
			client_start(info_client, info_item);
		else if (command == "0")
			break;
		else
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
	}

	write_info(info_client, info_item, "clients.txt", "items.txt");

	return 0;
}

void get_id_pw(string& id, string& pw) {
	cout << "ID�� �Է��ϼ���>>";
	cin >> id;
	cout << "��ȣ�� �Է��ϼ���>>";
	cin >> pw;
}


string get_command_admin() {
	string command;
	cout << "1. ��� ȸ������ ���" << endl;
	cout << "2. ȸ�� �˻�         " << endl;
	cout << "3. ȸ�� �߰�         " << endl;
	cout << "4. ȸ�� ����         " << endl;
	cout << "---------------------" << endl;
	cout << "5. ��� ��ǰ���� ���" << endl;
	cout << "6. ������� ��ǰ ���" << endl;
	cout << "7. ��ǰ �˻�         " << endl;
	cout << "8. ��ǰ �߰�         " << endl;
	cout << "9. ��ǰ ����         " << endl;
	cout << "---------------------" << endl;
	cout << "0. ����              " << endl;
	cout << ">>";
	cin >> command;
	return command;
}


void admin_start(Matrix& info_client, Matrix& info_item) {
	string id, pw, command;
	get_id_pw(id, pw);
	if (id == "admin" && pw == "0000") {
		cout << "�α��� �Ϸ�." << endl << endl;
		while (true) {
			command = get_command_admin();
			if (command == "1")		 print_all(info_client);
			else if (command == "2") search_client_by_id(info_client, id);
			else if (command == "3") add_client(info_client);
			else if (command == "4") delete_client(info_client);
			else if (command == "5") print_all(info_item);
			else if (command == "6") print_items_by_region(info_client, info_item);
			else if (command == "7") search_item_by_id(info_item, id);
			else if (command == "8") add_item(info_item);
			else if (command == "9") delete_item(info_item);
			else if (command == "0") break;

			else                     cout << "�߸� �Է��Ͽ����ϴ�." << endl << endl;
		}
	}
	else {
		cout << "ID �Ǵ� ��ȣ�� �߸��Ǿ����ϴ�." << endl << endl;
	}
}

void read_info(Matrix& info_client, Matrix& info_item, string filename_client, string filename_item) {
	/* ���: filename_client�� filename_item�� ������ info_client�� info_item�� ������ ��
	   �䱸����1: ������ ����� ������ �ʴ� ��� "������ �������� �ʽ��ϴ�"�� ȭ�鿡 ����ϰ� exit(100)�� �̿��Ͽ� ���α׷� ��������
	   �䱸����2: ���� �б⸦ ��ģ �� �ݵ�� ������
	   ����: info_client�� info_item�� ���� �� vector element�� ù ��° element�� ���� ȸ��(�Ǵ� ��ǰ)������ �ƴ� �Ʒ��� label�� ����:
			 - info_client:     ID  Password    Region       Order_Item_ID
			 - info_item:	    ID            ItemName     Price  Quantity
	 */

	ifstream fin_client;
	ifstream fin_item;

	string clientID, Password, Region, Order_item_ID;
	string itemID, ItemName, Price, Quantity;

	fin_client.open(filename_client);
	fin_item.open(filename_item);

	if (!fin_client && !fin_item)
	{
		cout << "������ �������� �ʽ��ϴ�." << endl;
		exit(100);
	}


	while (true)
	{
		fin_client >> clientID >> Password >> Region >> Order_item_ID;
		if (!fin_client)
			break;
		else
		{
			info_client[CLIENT_ID].push_back(clientID);
			info_client[CLIENT_PW].push_back(Password);
			info_client[CLIENT_REGION].push_back(Region);
			info_client[CLIENT_ORDER_LIST].push_back(Order_item_ID);
		}
	}

	while (true)
	{
		fin_item >> itemID >> ItemName >> Price >> Quantity;
		if (!fin_item)
			break;
		else
		{
			info_item[ITEM_ID].push_back(itemID);
			info_item[ITEM_NAME].push_back(ItemName);
			info_item[ITEM_PRICE].push_back(Price);
			info_item[ITEM_QUANTITY].push_back(Quantity);
		}
	}

	fin_client.close();
	fin_item.close();
	// ...
	cout << "���� �б� �Ϸ�." << endl << endl;

}


void write_info(const Matrix& info_client, const Matrix& info_item, string filename_client, string filename_item) {
	/* ���: info_client�� info_item�� ������ filename_client�� filename_item�� ������ ��
	  �䱸����1: ���� ���⸦ ��ģ �� �ݵ�� ������
	*/

	ofstream fout_client;
	ofstream fout_item;
	fout_client.open(filename_client);
	fout_item.open(filename_item);

	for (int i = 0; i < info_client[CLIENT_ID].size(); i++)
	{
		fout_client << setw(15) << info_client[CLIENT_ID][i];
		fout_client << setw(15) << info_client[CLIENT_PW][i];
		fout_client << setw(15) << info_client[CLIENT_REGION][i];
		fout_client << setw(15) << info_client[CLIENT_ORDER_LIST][i];
		fout_client << endl;
	}

	for (int i = 0; i < info_item[ITEM_ID].size(); i++)
	{
		fout_item << setw(15) << info_item[ITEM_ID][i];
		fout_item << setw(15) << info_item[ITEM_NAME][i];
		fout_item << setw(15) << info_item[ITEM_PRICE][i];
		fout_item << setw(15) << info_item[ITEM_QUANTITY][i];
		fout_item << endl;
	}

	fout_client.close();
	fout_item.close();
	// ...	
	cout << "����Ϸ� - ���α׷��� �����մϴ�." << endl;
}


void print_each(const Matrix& info, int index) {
	/* ���: �ش� index�� �ش��ϴ� info_item(�Ǵ� info_client)�� ������ ȭ�鿡 ���
	   �䱸����: setw(15)�� �̿��Ͽ� �� element�� ������ ���� ��
	*/


	for (int i = 0; i < info.size(); i++)
	{
		cout << setw(15) << info[i][index];
	}
	cout << endl;

}


void print_all(const Matrix& info) {
	/* ���: info_item(�Ǵ� info_client)�� ������ ȭ�鿡 ���
	   �䱸����1: �� item(�Ǵ� client)�� �ݵ�� print_each()�Լ��� ����ؼ� ȭ�鿡 ���
	*/

	for (int index = 0; index < info[CLIENT_ID].size(); index++)
	{
		print_each(info, index);
	}
	cout << endl;

}


vector<string> extract_regions(const Matrix& info_client) {
	/* ���: ȸ���� ���� ������ �ߺ��� ������� �ʰ� vector�� element�� ������ ���� �ش� vector�� ��ȯ
	   ��: ȸ���� ������ (����, ����, �λ�, �λ� �λ�, ����) �� ��� --> (����, �λ�, ����) ���� �ߺ��� ����
		   �̶� ������ ��� ������ �������(���ĵ��� �ʾƵ� ��)
	*/

	vector<string> regions;

	for (int i = 1; i < info_client[CLIENT_REGION].size(); i++)
	{
		bool bIsin = false;
		for (int index = 0; index < regions.size(); index++)
		{

			if (regions[index] == info_client[CLIENT_REGION][i])
			{
				bIsin = true;
				break;
			}
		}
		if (bIsin == false)
		{
			regions.push_back(info_client[CLIENT_REGION][i]);
		}
	}

	// ...

	return regions;
}


void print_items_by_region(const Matrix& info_client, const Matrix& info_item) {
	/* ���: ���θ��� ����� ���� �������� �ֹ��� ��ǰ���� ������ ȭ�鿡 ����� ��
	   �䱸����: �Ʒ� regions�� �ݵ�� ����� ��
	   ����: �� ������ ���� ��ǰ ID�� ��µ� �� ������, ���ĵ��� �ʾƵ� ��(���� ���, ����: F04,C01,F04,)
	*/

	vector<string> regions = extract_regions(info_client);
	string store;

	for (int i = 0; i < regions.size(); i++)
	{
		for (int index = 1; index < info_client[CLIENT_REGION].size(); index++)
		{
			if (regions[i] == info_client[CLIENT_REGION][index])
			{
				store += info_client[CLIENT_ORDER_LIST][index];
				store += ",";
			}
		}
		cout << setw(10) << regions[i] << ": " << store << endl;
		store.clear();
	}
	cout << endl;
	// ...
}


int search_item_by_id(const Matrix& info_item, string& id) {
	/* ���: ID�� Ű����κ��� �Է¹޾� info_item���� �ش� id�� ������ id�� ã����� label�� item�� ���� ������ ȭ�鿡 ����ϰ� vector�� �ش� index�� ��ȯ
			 ���� ������ id�� ã�� ���ϸ� -1�� ��ȯ
	*/

	cout << "ID�� �Է��ϼ���>>";
	cin >> id;
	// ...

	int i = 0;
	bool bfind = false;

	for (i = 1; i < info_item[ITEM_ID].size(); i++)
	{
		if (info_item[ITEM_ID][i] == id)
		{
			bfind = true;
			break;
		}
	}

	if (bfind == true)
	{
		for (int index = 0; index < info_item.size(); index++)
		{
			cout << setw(15) << info_item[index][0];
		}
		cout << endl;
		for (int j = 0; j < info_item.size(); j++)
		{
			cout << setw(15) << info_item[j][i];
		}
		cout << endl << endl;

		return i;
	}

	cout << endl;
	return -1;
}


int search_client_by_id(const Matrix& info_client, string& id) {
	/* ���: ID�� Ű����κ��� �Է¹޾� info_client���� �ش� id�� ������ id�� ã����� label�� client�� ���� ������ ȭ�鿡 ����ϰ� vector�� �ش� index�� ��ȯ
			 ���� ������ id�� ã�� ���ϸ� -1�� ��ȯ
	*/

	cout << "ID�� �Է��ϼ���>>";
	cin >> id;
	// ...

	int i = 0;
	bool bfind = false;

	for (i = 1; i < info_client[CLIENT_ID].size(); i++)
	{
		if (info_client[CLIENT_ID][i] == id)
		{
			bfind = true;
			break;
		}
	}

	if (bfind == true)
	{
		for (int index = 0; index < info_client.size(); index++)
		{
			cout << setw(15) << info_client[index][0];
		}
		cout << endl;
		for (int j = 0; j < info_client.size(); j++)
		{
			cout << setw(15) << info_client[j][i];
		}
		cout << endl << endl;

		return i;
	}

	cout << endl;

	return -1;
}


void add_client(Matrix& info_client) {
	/* ���: id�� Ű����� ���� �Է¹޾�, �ش� id�� ���� ���� info_client�� �̹� �����ϸ� "������ ID�� �����մϴ�"�� ȭ�鿡 ���
			 �׷��� ������ �߰��� ��й�ȣ�� ������ �Է����� �޾� vector���� ���� ������ �κп� �߰�(�̶�, info_client[CLIENT_ORDER_LIST]���� "N/A" ���ڿ��� �߰�)
	   �䱸����: search_client_by_id()�� ����ؼ� id�� �����ϴ��� ã�� ��
	*/
	string id, password, region;

	//cout << "ID�� �Է��ϼ���>>";
	//cin >> id;

	if (search_client_by_id(info_client, id) == -1)
	{
		cout << "��й�ȣ�� �Է��ϼ���>>";
		cin >> password;
		cout << "������ �Է��ϼ���>>";
		cin >> region;

		info_client[CLIENT_ID].push_back(id);
		info_client[CLIENT_PW].push_back(password);
		info_client[CLIENT_REGION].push_back(region);
		info_client[CLIENT_ORDER_LIST].push_back("N/A");

		cout << "�߰� �Ϸ�." << endl << endl;;
	}

	else
	{
		cout << "������ ID�� �����մϴ�." << endl << endl;
	}

}


void delete_client(Matrix& info_client) {
	/* ���: id�� Ű����� ���� �Է¹޾�, �ش� id�� ���� ���� info_client�� �̹� �������� ������ "ID�� �������� �ʽ��ϴ�"�� ȭ�鿡 ���
			 ������ ��� �ش� �������� vector���� ������ ��
			 (��Ʈ: �����ؾ� �� element�� index�� i���, [i+1]��° element�� [i]��° element�� �����ϰ�, �̸� ������ element���� �ݺ� �� pop_back()���)
	�䱸����: search_client_by_id()�� ����ؼ� id�� �����ϴ��� ã�� ��
	*/

	string id;

	int index = search_client_by_id(info_client, id);

	if (index == -1)
	{
		cout << "ID�� �������� �ʽ��ϴ�." << endl << endl;
	}

	else
	{
		for (int i = 0; i < info_client.size(); i++)
		{
			info_client[i].erase(info_client[i].begin() + index);
		}
		cout << "�����Ǿ����ϴ�." << endl << endl;
	}

}


void add_item(Matrix& info_item) {
	/* ���: id�� Ű����� ���� �Է¹޾�, �ش� id�� ���� ��ǰ�� info_item�� �̹� �����ϸ� "������ ID�� �����մϴ�"�� ȭ�鿡 ���
			 �׷��� ������ �߰��� ��ǰ��� ������ �Է����� �޾� vector���� ���� ������ �κп� �߰�(��ǰ��, ������ ���ڵ� ��� string���ڿ��� ó���� ��)
			 �䱸����: search_item_by_id()�� ����ؼ� id�� �����ϴ��� ã�� ��
	*/

	string id, name, price, quantity;



	if (search_item_by_id(info_item, id) == -1)
	{
		cout << "��ǰ���� �Է��ϼ���>>";
		cin >> name;
		cout << "������ �Է��ϼ���>>";
		cin >> price;
		cout << "������ �Է��ϼ���>>";
		cin >> quantity;

		info_item[ITEM_ID].push_back(id);
		info_item[ITEM_NAME].push_back(name);
		info_item[ITEM_PRICE].push_back(price);
		info_item[ITEM_QUANTITY].push_back(quantity);


		cout << "�߰� �Ϸ�." << endl << endl;;
	}

	else
	{
		cout << "������ ID�� �����մϴ�." << endl << endl;
	}

}


void delete_item(Matrix& info_item) {
	/* ���: id�� Ű����� ���� �Է¹޾�, �ش� id�� ���� ��ǰ�� info_client�� �̹� �������� ������ "ID�� �������� �ʽ��ϴ�"�� ȭ�鿡 ���
			 ������ ���, �ش� ��ǰ������ vector���� ������ ��
			 (��Ʈ: �����ؾ� �� element�� index�� i���, [i+1]��° element�� [i]��° element�� �����ϰ�, �̸� ������ element���� �ݺ� �� pop_back()���)
	�䱸����: search_item_by_id()�� ����ؼ� id�� �����ϴ��� ã�� ��
	*/


	string id;

	int index = search_item_by_id(info_item, id);

	if (index == -1)
	{
		cout << "ID�� �������� �ʽ��ϴ�." << endl << endl;
	}

	else
	{
		for (int i = 0; i < info_item.size(); i++)
		{
			info_item[i].erase(info_item[i].begin() + index);
		}
		cout << "�����Ǿ����ϴ�." << endl << endl;
	}
}





void client_start(Matrix& info_client, Matrix& info_item) {
	/* ���: �Ʒ��� ��ɵ��� ������ ��� ������ (����� ���̵� �� ������ ����) �߰�
	(������ ���̵��� ����)����ִ� ����� �����ص���
	����� ��: �α��� �� password ����, �ֹ��� ��ǰ ���� ��ȸ(ID�� �̿��ؼ� �� ��ǰ�� ������ ȭ�鿡 ���) ��ǰ �ֹ�, ��ǰ ���� Ȯ�� ��
	�䱸����: �� ��ɵ��� �Լ��� ������ ��
	�䱸����: �� ��ɵ鿡 ���� ����ó���� �Ϻ��ؾ� ��(���� ���, '��ǰ �ֹ�' �� ������ ���� ��ǰ�� �ֹ��ϸ� "������ �����մϴ�"�� ȭ�鿡 ����ϰ� �ֹ��� ��ҵǾ�� ��)
	*/

	string command;

	while (true)
	{
		command = get_command_client();

		if (command == "1")		 print_all(info_item);
		else if (command == "2") create_account(info_client);
		else if (command == "3") sign_in(info_client, info_item);
		else if (command == "0") break;

		else                     cout << "�߸� �Է��Ͽ����ϴ�." << endl << endl;
	}
}

string get_command_client()
{
	string command;
	cout << endl;
	cout << "1. ��ǰ �ѷ�����" << endl;
	cout << "2. ȸ������" << endl;
	cout << "3. �α���" << endl;
	cout << "---------------------" << endl;
	cout << "0. ����" << endl;
	cout << ">>";
	cin >> command;

	return command;

}

int id_exists(Matrix& info_client, string& id)
{

	for (int i = 1; i < info_client[CLIENT_ID].size(); i++)
	{
		if (id == info_client[CLIENT_ID][i])
		{
			return i;
		}
	}
	return 0;
}
bool pw_exists(Matrix& info_client, string& password)
{
	bool bFind = false;

	for (int i = 1; i < info_client[CLIENT_PW].size(); i++)
	{
		if (password == info_client[CLIENT_PW][i])
		{
			bFind = true;
			break;
		}
	}
	return bFind;
}

void create_account(Matrix& info_client)
{
	string id, password, region;
	cout << "ID�� �Է��ϼ���>>";
	cin >> id;

	if (id_exists(info_client, id) == false)
	{
		cout << "��й�ȣ�� �Է��ϼ���>>";
		cin >> password;
		cout << "������ �Է��ϼ���>>";
		cin >> region;

		info_client[CLIENT_ID].push_back(id);
		info_client[CLIENT_PW].push_back(password);
		info_client[CLIENT_REGION].push_back(region);
		info_client[CLIENT_ORDER_LIST].push_back("N/A");

		cout << endl << "ȸ�������� �Ϸ�Ǿ����ϴ�!" << endl << endl;
	}

	else
	{
		cout << "�̹� �����ϴ� ID �Դϴ�." << endl;
	}
}



void sign_in(Matrix& info_client, Matrix& info_item)
{
	string id, password, region;
	string choice;
	cout << "ID�� �Է��ϼ���>>";
	cin >> id;
	if (id_exists(info_client, id) != 0)
	{
		cout << "��й�ȣ�� �Է��ϼ���>>";
		cin >> password;
		if (pw_exists(info_client, password) == true)
		{
			int client_id = id_exists(info_client, id);
			cout << "�α��� �Ϸ�" << endl;
			MyCoupang(info_client, info_item, client_id);
		}
		else
			cout << "��й�ȣ�� Ʋ���ϴ�." << endl << endl;
	}
	else
	{
		cout << "�������� �ʴ� ID �Դϴ�." << endl;
	}
}


void item_exists(Matrix& info_client, Matrix& info_item, string& item_id, int& client_id)
{
	int quantity;
	bool bFind = false;
	for (int i = 1; i < info_item[ITEM_ID].size(); i++)
	{
		if (info_item[ITEM_ID][i] == item_id)
		{
			bFind = true;
			cout << "��ǰ�� ������ �Է��ϼ���>>";
			cin >> quantity;
			if (quantity <= 0)
			{
				cout << "1 �̻��� ������ �Է����ּ���." << endl;
				break;
			}

			int itemQuantity = stoi(info_item[ITEM_QUANTITY][i]);
			int stock = itemQuantity - quantity;
			if (stock >= 0)
			{
		
				info_item[ITEM_QUANTITY][i] = to_string(stock);
				if (info_client[CLIENT_ORDER_LIST][client_id] == "N/A")
				{
					info_client[CLIENT_ORDER_LIST][client_id].erase();
					info_client[CLIENT_ORDER_LIST][client_id] += info_item[ITEM_ID][i];
				}
				else
				{
					info_client[CLIENT_ORDER_LIST][client_id] += "," + info_item[ITEM_ID][i];
				}

				cout << "���Ű� �Ϸ�Ǿ����ϴ�!" << endl;

			}

			else
			{
				cout << "��� �����Ͽ� �ֹ��� �� �����ϴ�." << endl << endl;
				break;
			}
		}
	}
	if (bFind == false)
	{
		cout << "�������� �ʴ� ��ǰ�Դϴ�." << endl << endl;
	}

}

void shopping(Matrix& info_client, Matrix& info_item, int& client_id)
{
	string id;
	print_all(info_item);
	cout << "������ ���Ͻô� ��ǰ�� ID�� �Է����ּ���>>";
	cin >> id;
	item_exists(info_client, info_item, id, client_id);
}

void printMe(const Matrix& info_client, int& client_id)
{
	print_each(info_client, 0);
	print_each(info_client, client_id);
}

void editMe(Matrix& info_client, int& client_id)
{
	string pw;
	string newPW, newRegion;
	string choice;
	cout << "��й�ȣ�� �Է��ϼ���>>";
	cin >> pw;
	if (pw == info_client[CLIENT_PW][client_id])
	{
		cout << "1. ��й�ȣ ����" << endl;
		cout << "2. ���� ����" << endl;
		cout << ">>";
		cin >> choice;
		if (choice == "1")
		{
			cout << "���ο� ��й�ȣ�� �Է��ϼ���>>";
			cin >> newPW;
			if (pw == newPW)
			{
				cout << "���� ��й�ȣ�� �����մϴ�." << endl << endl;

			}
			else
			{
				info_client[CLIENT_PW][client_id] = newPW;
				cout << "������ �Ϸ�Ǿ����ϴ�." << endl << endl;
			}
		}
		else if (choice == "2")
		{
			cout << "���ο� ������ �Է��ϼ���>>";
			cin >> newRegion;
			if (newRegion == info_client[CLIENT_REGION][client_id])
			{
				cout << "���� ������ �����մϴ�." << endl << endl;
			}
			else
			{
				info_client[CLIENT_REGION][client_id] = newRegion;
				cout << "������ �Ϸ�Ǿ����ϴ�." << endl << endl;
			}
		}

		else
		{
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl << endl;
		}
	}
	else
	{
		cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." <<endl<<endl;
	}
}

bool leave(Matrix& info_client, int& client_id)
{
	string pw;
	string choice;
	cout << "��й�ȣ�� �Է��ϼ���>>";
	cin >> pw;
	if (pw == info_client[CLIENT_PW][client_id])
	{
		cout << endl << "������ �� ���� ��ǰ�� �̺�Ʈ�� �غ��ϵ��� �ϰڽ��ϴ�. �Ф�." << endl;
		cout << "�׷��� ���� Ż���Ͻðڽ��ϱ�?" << endl;
		cout << "1.��  2.�ƴϿ� >>";
		cin >> choice;
		if (choice == "1")
		{
			info_client[CLIENT_ID][client_id].erase();
			info_client[CLIENT_PW][client_id].erase();
			info_client[CLIENT_REGION][client_id].erase();
			info_client[CLIENT_ORDER_LIST][client_id].erase();
			cout << "Ż��Ǿ����ϴ�. �̿����ּż� �����մϴ�." << endl << endl;
			return true;
		}
		else
		{
			cout << "�����մϴ�! �� �����ϴ� ������ �ǵ��� �ϰڽ��ϴ�." << endl << endl;
			
		}
	}
	else
	{
		cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl << endl;
	}
	return false;
}


string get_command_myCoupang()
{
	string command;
	cout << endl;
	cout << "1. �����ϱ�" << endl;
	cout << "2. �� ���� �����ϱ�" << endl;
	cout << "3. �� ���� ����" << endl;
	cout << "4. Ż���ϱ�" << endl;
	cout << "---------------------" << endl;
	cout << "0. ����" << endl;
	cout << ">>";
	cin >> command;

	return command;
}

void MyCoupang(Matrix& info_client, Matrix& info_item, int& client_id) {

	string command;

	while (true)
	{
		command = get_command_myCoupang();

		if (command == "1")		 shopping(info_client, info_item, client_id);
		else if (command == "2") editMe(info_client, client_id);
		else if (command == "3") printMe(info_client, client_id);
		else if (command == "4")
		{
			if (leave(info_client, client_id) == true)
				break;
		}
		else if (command == "0") break;

		else                     cout << "�߸� �Է��Ͽ����ϴ�." << endl << endl;
	}
}
