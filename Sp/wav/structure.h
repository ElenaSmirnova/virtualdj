typedef struct SoundBuffer {
public:
	int **buff;// - указатель
	long frequency;// частота выборки
private:
	long len_buff;// - длина динамического массива
public:
	void setLength(long len_buff){
		this->len_buff = len_buff;
		buff = (int **)calloc(this->len_buff,sizeof(int *));
		for (int i=0; i < this->len_buff; i++)
		{
				  buff[i]=(int *)calloc(2, sizeof(int));
		}
	}
	SoundBuffer(int **buffer, long len_buff, long frequency){
		buff = buffer;
		setLength(len_buff);
		this->frequency = frequency;
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