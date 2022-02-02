
# API

## 소개

클라이언트와 서버간의 주고받는 문자열의 규칙을 알려주는 페이지입니다.

## Client To Server

| First Code | Second Code | API 내용 | API 설명 |
|:---:|:---:|---|---|
| 0 | 0 | id </br> userName| 유저 생성|
|         | 1 | roomid | 유저 리스트 전달 |
| 1 | 0 | roomid | 채팅리스트 요청 |
|         | 1 | roomid </br> id </br> chatText |   |
| 2 |   |   | 게임 |
| 3 | 0 | userid </br> roomName </br> roomMaxPeople | 방 만들기 |
|         | 1 | roomid </br> userid | 사람 참가 |
|         | 2 | roomid </br> userid | 레디 |
|         | 3 | userid | 방 리스트 요청 |
| 4 | 1 | 0 'up' </br>    1~6 '숫자' </br> 1 'bonus' </br> 2 'down' </br>    1~6 '숫자' | 주사위 결과 선택 |
|         | 2 | roomid </br> mask '문자열로 주사위 선택(0 : 돌리기, 1: 락)' | 주사위 돌리기 |
|         | 3 | roomid </br> lockinfo | 주사위 락 정보 |
|         | 4 | roomid | input 'x' |


## Server To Client

| First Code | Second Code | API 내용 | API 설명 |
|:---:|:---:|---|---|
| 0 | 0 | roomid </br> roomName </br> roomMaxPeople | 방 정보 전달 |
|         | 1 | roomList_count </br> { </br> roomid </br> roomName </br> roomMaxPeople</br> } | 방 리스트 전달 |
|         | 2 |   | gameroom으로 변경 |
| 1 | 0 | userlist_count </br> { </br> user->id </br> user->name </br> user->isReady </br> } | 유저 리스트 전달 |
|         | 1 | chatlist_count </br> { </br> chat_str </br> } | chat 정보 |
|         | 2 | user->id </br> user->name </br> user->isReady | add_user |
| 2 | 1 | 5개의 주사위 값 전달 | 주사위 값 |
|         | 2 | id </br> { </br> up 6개 </br> choice </br> down 6개 </br> } | 유저 스코어보드 전달 |
|         | 3 | lockinfo | 주사위 락 정보 |
|         | 4 | scoreinfo | 점수판 정보 |
|         | 5 |   | 순서 변경 |