# swc-homework
보안개론 2번째 실습과제입니다. 이번과제는 UAF와 Double Free Bug를 이용하여 서버측에서 동작하는 프로그램의 특정 함수를 호출하는 과제입니다. 

> [!CAUTION]
> Podman 환경에서는 정상적이 동작이 되지 않을 수 있습니다
> Docker 사용을 권장합니다. 

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

## 도커 설치
- 우분투 & WSL (22.04)
```BASH
sudo apt update 
sudo apt install apt-transport-https ca-certificates curl gnupg-agent software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io
```

- 우분투 & WSL (24.04)
https://docs.docker.com/engine/install/ubuntu/
```BASH
# 이전 버전 제거
for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove $pkg; done

# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update

sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```