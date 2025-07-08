# 주제 : hello_world systemcall 만들기

## 리눅스 ubuntu를 사용.

 커널에 빌드하여 커널이 작업하는 systemcall을 만드는것을 목표로 실시하였습니다.
 과정 : 
    1. 시스템 추가를 위해 linux-*/arch/x86/entry/syscalls/syscall_64.tbl에 실행 파일 추가
    2. 헤더파일 추가 : linux-*/include/linux/syscall.h 파일에 어셈블리어 추가
    3. 재빌드 및 리붓

 어려웠던 점 : 커널 빌드 과정에 계속 오류가 발생
