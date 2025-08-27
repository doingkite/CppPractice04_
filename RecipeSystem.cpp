#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // find

using namespace std;

// PotionRecipe 클래스: 물약 이름과 재료 목록
class PotionRecipe {
public:
    string potionName;
    vector<string> ingredients;
    int stock; // + 현재 재고

    PotionRecipe(const string& name, const vector<string>& ingredients)
        : potionName(name), ingredients(ingredients), stock(3) {
    } //초기 재고 추가
};

// AlchemyWorkshop: 레시피 목록 관리
class AlchemyWorkshop {
private:
    vector<PotionRecipe> recipes;

public:
    // 레시피 추가
    void addRecipe(const string& name, const vector<string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        cout << ">>새로운 레시피 '" << name << "'이(가) 추가되었습니다." << endl;
    }

    // 레시피 전체 조회
    void displayAllRecipes() const {
        if (recipes.empty()) {
            cout << "등록된 레시피가 없음" << endl;
            return;
        }
        cout << "\n[전체 레시피 목록]\n";
        for (size_t i = 0; i < recipes.size(); ++i) {
            cout << "물약 이름: " << recipes[i].potionName << endl;
            cout << " >> 필요 재료: ";
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                cout << recipes[i].ingredients[j];
                if (j < recipes[i].ingredients.size() - 1) cout << ", ";
            }
            cout << endl << "---------------------------\n";
        }
    }

    // 물약 이름 검색
    vector<PotionRecipe>::iterator searchRecipesByName(const string& name) {
        for (auto iter = recipes.begin(); iter != recipes.end(); ++iter) {
            if (iter->potionName == name) return iter;
        }
        return recipes.end();
    }

    // 재료 검색
    vector<PotionRecipe>::iterator searchRecipeByIngredient(const string& ingredient) {
        for (auto iter = recipes.begin(); iter != recipes.end(); ++iter) {
            if (find(iter->ingredients.begin(), iter->ingredients.end(), ingredient) != iter->ingredients.end()) {
                return iter;
            }
        }
        return recipes.end();
    }

    // 특정 물약의 현재 재고 수량
    int initializeStock(const string& name) {
        auto it = searchRecipesByName(name);
        if (it != recipes.end()) {
            return it->stock;
        }
        else {
            cout << "해당 물약은 존재하지 않습니다." << endl;
            return -1;
        }
    }

    // 물약 이름으로 재고 검색 후 1개 이상인 경우 모험가에게 지급
    bool dispensePotion(const string& name) {
        auto it = searchRecipesByName(name);
        if (it != recipes.end()) {
            if (it->stock >= 1) {
                it->stock--; //재고 감소
                cout << it->potionName << " 지급 완료, 남은 재고: " << it->stock << "개" << endl;
                return true;
            }
            else {
                cout << "재고부족" << endl;
                return false;
            }
        }
        cout << "해당 물약은 존재하지 않습니다." << endl;
        return false;
    }

    // 모험가에게 지급했던 물약의 공병을 다시 반환 받을 수 있어야 함
    void returnPotion(const string& name) {
        auto it = searchRecipesByName(name);
        if (it != recipes.end()) {
            if (it->stock < 3) {
                it->stock++; // 다시 재고 채우기
                cout << it->potionName << "이(가) 반환되었습니다. 남은 재고: " << it->stock << " 개" << endl;
            }
            else {
                cout << "반환할 수 없습니다." << endl;
            }
        }
        else {
            cout << "해당 물약은 존재하지 않습니다." << endl;
        }
    }

    // 레시피 벡터 반환
    const vector<PotionRecipe>& getRecipes() const { return recipes; }
};


int main() {
    AlchemyWorkshop myWorkshop;

    // 테스트용 초기 레시피
    myWorkshop.addRecipe("힐링 포션", { "허브", "물", "레드 크리스탈" });
    myWorkshop.addRecipe("마나 포션", { "마나꽃", "물", "블루 크리스탈" });
    myWorkshop.addRecipe("스태미나 포션", { "당근", "허브", "물" });
    myWorkshop.addRecipe("독 해독제", { "민트", "레몬", "물" });
    myWorkshop.addRecipe("힘의 포션", { "곡물", "마법의 뿌리", "물" });
    myWorkshop.addRecipe("속도 증가 포션", { "은빛 잎", "물", "바람의 가루" });

    while (true) {
        cout << "⚗️ 연금술 공방 관리 시스템\n";
        cout << "1. 레시피 추가\n";
        cout << "2. 모든 레시피 출력\n";
        cout << "3. 종료\n";
        cout << "선택: ";

        int choice;
        cin >> choice;

        if (cin.fail()) { // 잘못된 입력 처리
            cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n'); // 버퍼 정리

        if (choice == 1) {
            string name;
            cout << "물약 이름: ";
            getline(cin, name);
            vector<string> ingredients_input;
            string ingredient;

            // 이름 검색
            auto nameIt = myWorkshop.searchRecipesByName(name);
            if (nameIt != myWorkshop.getRecipes().end()) {
                cout << "이미 존재하는 물약입니다: " << nameIt->potionName << endl;
            }
            // 재고 확인 함수
            int stock = myWorkshop.initializeStock(name);
            if (stock != -1) {
                cout << name << " 현재 재고: " << stock << " 개\n";
            }
            //지급 함수
            myWorkshop.dispensePotion(name);

            if (nameIt != myWorkshop.getRecipes().end())

                //반환 함수
                myWorkshop.returnPotion(name);

            if (nameIt != myWorkshop.getRecipes().end())

                // 재료 입력

                cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)\n";
            while (true) {
                cout << "재료 입력: ";
                getline(cin, ingredient);
                if (ingredient == "끝") break;

                ingredients_input.push_back(ingredient);

                // 재료 검색
                auto ingIt = myWorkshop.searchRecipeByIngredient(ingredient);
                if (ingIt != myWorkshop.getRecipes().end()) {
                    cout << "재료 포함 레시피: " << ingIt->potionName << endl;
                }
                else {
                    cout << "해당 재료를 포함한 레시피가 없음" << endl;
                }
            }

            // 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();
        }
        else if (choice == 3) {
            cout << "공방 문을 닫습니다..." << endl;
            break;
        }
        else {
            cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}
