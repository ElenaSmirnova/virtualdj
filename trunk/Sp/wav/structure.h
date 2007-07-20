#include <windows.h>
#include <stdio.h>

typedef struct {
	char id_riff[4];//- ������������� ����� = "RIFF" = 0x46464952
    long len_riff;//- ����� ����� ��� ����� ���������

	char id_chuck[4];//- ������������� = "WAVE" = 0x45564157
	char fmt[4];//- ������������� = "fmt " = 0x20746D66
	long len_chuck; //- ����� ����� ����� WAV - �����,

	short int  type; //- ��� �������� ������
	short int  channels;//- ����� �������
	long freq;//- ������� ������� 
	long bytes;//- ������� ������ ������
	short int  align;//- ������������
	short int  bits;//- ����� ��� �� �������

	char id_data[4];//- ������������� ="data" =0x61746164
	long len_data;//  - ����� �������

} TitleWave;

struct SoundBuffer {
public:
	TitleWave titleWave;
	int **buff;// - ���������
	long lastSimbol;
private:
	long len_buff;// - ����� ������������� �������
public:
	void setLength(long len_buff){
		this->len_buff = len_buff;
		buff = (int **)calloc(this->len_buff,sizeof(int *));
		for (int i=0; i < this->len_buff; i++){
			buff[i]=(int *)calloc(2, sizeof(int));
		}
	}
	SoundBuffer(int **buffer, long len_buff){
		buff = buffer;
		setLength(len_buff);
		lastSimbol = 0;
		titleWave.align = 0;
		titleWave.bits = 0;
		titleWave.bytes = 0;
		titleWave.channels = 0;
		titleWave.freq = 0;
		titleWave.len_chuck = 0;
		titleWave.len_data = 0;
		titleWave.len_riff = 0;
		titleWave.type = 0;
	}
	~SoundBuffer(){
		for (int i=0; i<len_buff; i++){
			free(buff[i]);
		}
		free(buff);
	}
	long getLength(){
		return len_buff;
	}
};