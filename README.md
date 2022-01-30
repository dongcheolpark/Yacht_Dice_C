<h1> Yacht_Dice_C <a href="https://github.com/dongcheolpark/Yacht_Dice_C/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-4aaa4a"></a></h1>

## 프로젝트 설명

요트다이스를 리눅스 터미널 상에서 구현하는 프로젝트입니다.

요트다이스란, 주사위 게임의 한 종류로 한국에서는 닌텐도 스위치에 출시된 51 Worldwide Games라는 게임에 수록된 게임으로 많이 알려져 있습니다. 이 프로젝트에서는 위 게임의 룰을 따릅니다. 

## 사용 기술
 - C++11
 - 멀티 플렉싱 서버
 - C style tcp 소켓 통신 

## 동작 운영체제
Linux, Windows, Mac

## 주요 기능
- 방 별로 개별 게임 실행 가능
- 최대 인원 5명까지 접속해 플레이 가능

## 컴파일 방법
server/bin, client/bin 폴더 생성 후 bin 폴더 내에서 
>$ cmake ..

커맨드 입력

빌드하려면 
>$ make 

커맨드 입력

프로그램 파일은 Server/bin 폴더의 Yacht_Dice_Server, Client/bin 폴더의 Yacht_Dice_Client입니다.


