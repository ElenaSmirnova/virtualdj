typedef struct Buffer {
public:
	int **buff;// - ���������
	long len_buff;// - ����� ������������� �������
	long frequency;// ������� �������
public:
	Buffer(int **buffer, long len_buff, long frequency){
		this->buff = buff;
		this->len_buff = len_buff;
		this->frequency = frequency;
	}
	Buffer(){
		Buffer(NULL, 0, 0);
	}
};