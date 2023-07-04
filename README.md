# UDT-flooding

C&C server에 접속해서 공격지IP와 포트정보를 받아 UDP flooding을 하는 악성코드 
- 악성코드는 서버에 10004번 포트로 IMHACKER_학번 메시지를 전송(UDP)한다.
- C&C Server로 부터 공격 대상지 IP와 PORT번호를 받고 공격지에 UDP flooding공격을 수행한다.
- 악성코드 분석가를 방해하기 위해 클라이언트 모듈 내부에 서버주소는 인코딩 또는 암호화 기능 추가한다.


### flowchart
<img src = "https://github.com/yejincode/UDT-flooding/assets/69861207/e6e27f8d-860a-46d0-9050-34e0016bdaba" width=500>

