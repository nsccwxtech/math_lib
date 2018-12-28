program test
implicit none
include "para.h"
real*8,dimension(M,N)::A
real*8,dimension(N,K)::B
real*8,dimension(M,K)::C
real*8,dimension(M,K)::C1
integer i,j,l
double precision st,ed
do j=1,N
do i=1,M
        A(i,j)=i/50.0+j/40.0
enddo
enddo

do j=1,K
do i=1,N
        B(i,j)=i/20.0+j/50.0
enddo
enddo

do j=1,K
do i=1,M
        C(i,j)=1.0
        C1(i,j)=1.0
enddo
enddo

call TIMER(st)
do j=1,N
do l=1,K
do i=1,M
        C(i,l)=C(i,l)+A(i,j)*B(j,l)
enddo
enddo
enddo
call TIMER(ed)

print*,'main time :',ed-st
call TIMER(st)
call dgemm('N','N',M,K,N,1.0d0,A,M,B,N,1.0d0,C1,N)
call TIMER(ed)
print*,'slave time :',ed-st

do j=1,K
do i=1,M
        if(abs(C(i,j)-C1(i,j))>1.0e-3) print*,'erro!,i,j,C(i,j),C1(i,j):',i,j,C(i,j),C1(i,j)
enddo
enddo
print*,'end'




end program


      SUBROUTINE TIMER(T)
      IMPLICIT NONE 

      DOUBLE PRECISION,INTENT(INOUT)::T
      INTEGER:: VAL(8)

      CALL DATE_AND_TIME(VALUES=VAL)
      T=DBLE(VAL(8))*1D-3+DBLE(VAL(7))+DBLE(VAL(6))*60D0+DBLE(VAL(5))*3600D0
      END SUBROUTINE TIMER





 
