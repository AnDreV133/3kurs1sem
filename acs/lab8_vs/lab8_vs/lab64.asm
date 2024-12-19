EXTERN printf: PROC

.data 
    fmt db "%d",10, 0

.code

; double* sort(double* res, double* a, int start, int end).
sort_fastcall_args_64  proc
    ; ���������� ���������
    push rbx
    push rsi
    push rdi
    push r12
    push r13
    push r14
    push r15

    ; ���������� ���������� �� ���������
    mov rdi, rcx        ; ��������� �� �������������� ������ res (RCX)
    mov rsi, rdx        ; ��������� �� �������� ������ a (RDX)
    mov rbx, r8        ; ������ ������ start (R8)
    mov rcx, r9        ; ������ ����� end (R9)

    ; ����������� ���������� � res
    sub ecx, ebx        ; ������ ����������
    inc ecx             ; ����������� �� 1, ����� �������� end
    xor edx, edx        ; ������ � res
copy_loop:
    mov rax, [rsi + rbx * 8] ; �������� �������� �� a[start]
    mov [rdi + rdx * 8], rax ; ���������� � res
    inc ebx                  ; ��������� ������ � a
    inc edx                  ; ��������� ������ � res
    loop copy_loop           ; ��������� ��� ���� ���������

    ; ������������� FPU
    finit

    ; ���������� ���������
    xor rcx, rcx
    mov ecx, r9d             
    sub ecx, r8d 
    inc ecx

sort_outer_loop:
    push rcx                 ; ��������� ������� �������� �����
    xor r13, r13           ; ������ ��� ����������� �����
sort_inner_loop:

    ; �������� �������� � ���������� ��������
    fld qword ptr [rdi + r13 * 8] ; �������� �������� ��������
    fld qword ptr [rdi + r13 * 8 + 8] ; �������� ���������� ��������

    ; ���������
    fcompp ; ��������� ���� ����� � ����� FPU � ������������ �� �� �����
    fstsw ax ; ���������� ����� ��������� FPU � AX
    sahf ; �������� AH � ������� ������

    ; �������, ���� ������� ������� <= ����������
    jbe no_swap

    ; ����� ����������
    fld qword ptr [rdi + r13 * 8] ; �������� �������� ��������
    fld qword ptr [rdi + r13 * 8 + 8] ; �������� ���������� ��������
    fstp qword ptr [rdi + r13 * 8] ; ���������� ���������� �������� �� ����� ��������
    fstp qword ptr [rdi + r13 * 8 + 8] ; ���������� �������� �������� �� ����� ����������

no_swap:
    inc r13d                  ; ��������� ������
    loop sort_inner_loop      ; ��������� ��� ���� ���������
    pop rcx                  ; ��������������� ������� �������� �����
    loop sort_outer_loop     ; ��������� ��� ���� ���������

    ; �������������� ���������
    pop r15
    pop r14
    pop r13
    pop r12
    pop rdi
    pop rsi
    pop rbx

    ; ������� ��������� �� res
    mov rax, rdi
    ret

sort_fastcall_args_64 endp

end