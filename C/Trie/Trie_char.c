#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

    
#define ALPHABET_SIZE 26

/* 문자 → 인덱스 변환 */
int trie_char_to_index(char c) {
    c = tolower((unsigned char)c);
    if ('a' <= c && c <= 'z') return c - 'a';
    return -1;
}

/* 영문자 단어인지 확인 */
int is_valid_word(const char* word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalpha((unsigned char)word[i]))
            return 0;
    }
    return 1;
}

/* Trie 노드 구조체 */
typedef struct Binary_Tree {
    struct Binary_Tree* children[ALPHABET_SIZE];
    int is_end;
} BT;

int word_count = 0;

/* 노드 생성 */
BT* BT_CreateNode() {
    BT* node = (BT*)malloc(sizeof(BT));
    node->is_end = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

/* 단어 검색 */
int BT_Search(BT* root, const char* word) {
    BT* cur = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = trie_char_to_index(word[i]);
        if (idx == -1) continue;
        if (!cur->children[idx]) return 0;
        cur = cur->children[idx];
    }
    return cur->is_end;
}

/* 단어 삽입 */
int BT_Insert(BT* root, const char* word) {
    if (BT_Search(root, word)) {
        printf("이미 존재하는 단어입니다: %s\n", word);
        return 0;
    }

    BT* cur = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = trie_char_to_index(word[i]);
        if (idx == -1) continue;
        if (!cur->children[idx])
            cur->children[idx] = BT_CreateNode();
        cur = cur->children[idx];
    }
    cur->is_end = 1;
    word_count++;
    printf("삽입 완료: %s\n", word);
    return 1;
}

/* 단어 삭제 */
int BT_Delete(BT* root, const char* word, int depth) {
    if (!root) return 0;

    if (word[depth] == '\0') {
        if (!root->is_end) return 0;
        root->is_end = 0;
        word_count--;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (root->children[i]) return 0;
        free(root);
        return 1;
    }

    int idx = trie_char_to_index(word[depth]);
    if (idx == -1) return BT_Delete(root, word, depth + 1);
    if (!root->children[idx]) return 0;

    int should_delete_child = BT_Delete(root->children[idx], word, depth + 1);
    if (should_delete_child)
        root->children[idx] = NULL;

    if (!root->is_end) {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (root->children[i]) return 0;
        free(root);
        return 1;
    }
    return 0;
}

/* 전체 단어 출력용 DFS */
void BT_PrintAll_Helper(BT* root, char* buf, int depth) {
    if (!root) return;
    if (root->is_end) {
        buf[depth] = '\0';
        printf("%s\n", buf);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            buf[depth] = 'a' + i;
            BT_PrintAll_Helper(root->children[i], buf, depth + 1);
        }
    }
}

/* 전체 단어 출력 */
void BT_PrintAll(BT* root) {
    char buf[256];
    BT_PrintAll_Helper(root, buf, 0);
}

/* 접두사 노드 찾기 */
BT* BT_FindPrefixNode(BT* root, const char* prefix) {
    BT* cur = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int idx = trie_char_to_index(prefix[i]);
        if (idx == -1) return NULL;
        if (!cur->children[idx]) return NULL;
        cur = cur->children[idx];
    }
    return cur;
}

/* 자동완성 */
void BT_AutoComplete(BT* root, const char* prefix) {
    BT* node = BT_FindPrefixNode(root, prefix);
    if (!node) {
        printf("'%s' 로 시작하는 단어가 없습니다.\n", prefix);
        return;
    }

    char buf[256];
    strcpy(buf, prefix);
    printf("\n--- 자동완성 결과 (%s...) ---\n", prefix);
    BT_PrintAll_Helper(node, buf, strlen(prefix));
    printf("\n혹시 위 단어 중 하나를 입력하고 싶으셨나요?\n");
}

/* 트라이 해제 */
void BT_Free(BT* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i]) BT_Free(root->children[i]);
    free(root);
}

/* 메뉴 출력 */
void print_menu() {
    system("cls");
    printf("===================================\n");
    printf("     Trie 단어 관리 프로그램\n");
    printf("===================================\n");
    printf("1. 단어 삽입\n");
    printf("2. 단어 삭제\n");
    printf("3. 단어 검색 (자동완성 포함)\n");
    printf("4. 단어 출력\n");
    printf("5. 종료\n");
    printf("-----------------------------------\n");
    printf("현재 저장된 단어 수: %d\n", word_count);
    printf("번호를 선택하세요: ");
}

int main() {
    BT* root = BT_CreateNode();
    int choice;
    char word[256];
    char cont;

    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar();
        system("cls");

        switch (choice) {
        case 1: // 삽입
            do {
                int n;
                printf("입력할 단어의 개수: ");
                scanf("%d", &n);
                getchar();
                for (int i = 0; i < n; i++) {
                    printf("%d번째 단어: ", i + 1);
                    scanf("%255s", word);
                    if (!is_valid_word(word)) {
                        printf("영문자(a~z)만 입력해주세요.\n");
                        i--;
                        continue;
                    }
                    BT_Insert(root, word);
                }
                printf("\n계속 입력하시겠습니까? (y/n): ");
                scanf(" %c", &cont);
                system("cls");
            } while (cont == 'y' || cont == 'Y');
            break;

        case 2: // 삭제
            do {
                if (word_count == 0) {
                    printf("삭제할 단어가 없습니다.\n");
                    system("pause");
                    break;
                }

                printf("현재 저장된 단어:\n");
                BT_PrintAll(root);

                printf("\n삭제할 단어: ");
                scanf("%255s", word);

                if (!is_valid_word(word)) {
                    printf("영문자(a~z)만 입력해주세요.\n");
                    continue;
                }

                if (BT_Search(root, word)) {
                    BT_Delete(root, word, 0);
                    printf("'%s' 삭제 완료.\n", word);
                }
                else {
                    printf("'%s' 가 존재하지 않습니다.\n", word);
                }

                printf("\n계속 삭제하시겠습니까? (y/n): ");
                scanf(" %c", &cont);
                system("cls");
            } while (cont == 'y' || cont == 'Y');
            break;

        case 3: // 검색 + 자동완성
            printf("검색할 단어 또는 접두어: ");
            scanf("%255s", word);

            if (!is_valid_word(word)) {
                printf("영문자(a~z)만 입력해주세요.\n");
                system("pause");
                break;
            }

            if (BT_Search(root, word)) {
                printf("'%s' 존재합니다.\n", word);
            }
            else {
                BT_AutoComplete(root, word);
            }

            system("pause");
            break;

        case 4: // 전체 출력
            if (word_count == 0)
                printf("저장된 단어가 없습니다.\n");
            else {
                printf("=== 저장된 단어 목록 ===\n");
                BT_PrintAll(root);
            }
            system("pause");
            break;

        case 5: // 종료
            printf("프로그램을 종료합니다.\n");
            BT_Free(root);
            system("pause");
            return 0;

        default:
            printf("잘못된 입력입니다.\n");
            system("pause");
            break;
        }
    }

    BT_Free(root);
    return 0;
}
