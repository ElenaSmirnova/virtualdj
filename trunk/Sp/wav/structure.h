#include <windows.h>
#include <stdio.h>

typedef struct {
	char id_riff[4];//- идентификатор файла = "RIFF" = 0x46464952
    long len_riff;//- длина файла без этого заголовка

	char id_chuck[4];//- идентификатор = "WAVE" = 0x45564157
	char fmt[4];//- идентификатор = "fmt " = 0x20746D66
	long len_chuck; //- длина этого куска WAV - файла,

	short int  type; //- тип звуковых данных
	short int  channels;//- число каналов
	long freq;//- частота выборки 
	long bytes;//- частота выдачи байтов
	short int  align;//- выравнивание
	short int  bits;//- число бит на выборку

	char id_data[4];//- идентификатор ="data" =0x61746164
	long len_data;//  - длина выборки

} TitleWave;

struct SoundBuffer {
public:
	TitleWave titleWave;
	int **buff;// - указатель
private:
	long len_buff;// - длина динамического массива
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