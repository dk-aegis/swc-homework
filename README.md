# swc-homework
보안개론 2번째 실습과제입니다. 이번과제는 UAF와 Double Free Bug를 이용하여 서버측에서 동작하는 프로그램의 특정 함수를 호출하는 과제입니다. 

### Build
빌드방법은 리눅스머신(호스트 or 가상머신) 또는 WSL에서만 가능합니다. (MACOS 불가능)   

#### 로컬빌드
```bash
git clone https://github.com/dk-aegis/swc-homework.git
cd swc-homework
make 
./chall
```

#### 도커빌드
```bash
git clone https://github.com/dk-aegis/swc-homework.git
cd swc-homework
make
docker run -d -p 5000:5000 --privileged $(docker build -q .)
```
도커빌드시 접속방법은 아래와 같습니다. 
```bash
nc 127.0.0.1 5000
```