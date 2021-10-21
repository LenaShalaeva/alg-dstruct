#pragma warning(disable : 4996)
#include "gtest/gtest.h"

extern "C" {
#include "logic.h"
}

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(check_order_test, checking_abc_order)
{
	char s1[21] = "ab";
	char s2[21] = "bab";
	EXPECT_EQ(check_order(s1, s2), 1);
	EXPECT_EQ(check_order(s2, s1), 0);
}

TEST(insert_beginning_test, adding_element_in_the_beginning) {
	Node* l1 = { NULL };
	l1->word = "bbb";
	Node* l2 = { NULL };
	l2->word = "ccc";
	l1->next = l2;

	insert_beginning(&l1, "aaa");
	EXPECT_TRUE(!strcmp(l1->word, "aaa"));
}

TEST(insert_end_test, adding_element_in_the_end) {
	Node* l1 = { NULL };
	l1->word = "bbb";
	Node* l2 = { NULL };
	l2->word = "ccc";
	l1->next = l2;

	insert_end(&l1, "aaa");
	EXPECT_TRUE(!strcmp(l1->next->next->word, "aaa"));
}

TEST(insert_after_test, adding_element_after_some_node) {
	Node* l1 = { NULL };
	l1->word = "bbb";
	Node* l2 = { NULL };
	l2->word = "ccc";
	l1->next = l2;

	insert_after(l1, "aaa");
	EXPECT_TRUE(!strcmp(l1->word, "bbb") && !strcmp(l1->next->word, "aaa") && !strcmp(l1->next->next->word, "ccc"));
}

TEST(add_sorted_test, adding_elements_in_sorted_order) {
	Node* list = NULL;

	add_sorted(&list, "bda");
	add_sorted(&list, "cab");
	add_sorted(&list, "abc");
	add_sorted(&list, "cad");

	EXPECT_TRUE(check_order(&list->word, &list->next->word));
	EXPECT_TRUE(check_order(&list->word, &list->next->word) && check_order(&list->next->word, &list->next->next->word));
	EXPECT_TRUE(check_order(&list->next->word, &list->next->next->word) && check_order(&list->next->next->word, &list->next->next->next->word));
}


TEST(sorted_merge_test, merging_two_sorted_lists_to_one_sorted_list) {
	Node* list1_1 = NULL;
	list1_1->word = "aaa";
	Node* list1_2 = { NULL };
	list1_2->word = "ccc";
	list1_1->next = list1_2;

	Node* list2_1 = NULL;
	list2_1->word = "bbb";
	Node* list2_2 = { NULL };
	list2_2->word = "ddd";
	list2_1->next = list2_2;

	Node* new_list = sorted_merge(list1, list2);

	EXPECT_TRUE(!strcmp(new_list->word, "aaa"));
	EXPECT_TRUE(!strcmp(new_list->next->word, "bbb"));
	EXPECT_TRUE(!strcmp(new_list->next->next->word, "ccc"));
	EXPECT_TRUE(!strcmp(new_list->next->next->next->word, "ddd"));

	int main(int argc, char* argv[]) {
		testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}

}