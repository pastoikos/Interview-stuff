

/*
===========================================================
                    PROBLEM DESCRIPTION
===========================================================

You are ordering pizza for a party.

You are given:

1) A MENU:
   Each pizza has:
       - name
       - price for Small
       - price for Medium
       - price for Large

2) An ORDER:
   Each order item contains:
       - name of pizza
       - size ("Small", "Medium", "Large")
       - quantity

Your goal:
Return the MINIMUM total cost of the order
using AT MOST ONE of the following discounts
(or none if no discount is beneficial).

-----------------------------------------------------------
DISCOUNT 1:
"Buy 3 pizzas, the cheapest one is free"
- If total pizzas >= 3
- One cheapest pizza in the whole order is free
- Can be used at most once

-----------------------------------------------------------
DISCOUNT 2:
"Buy 5 pizzas of the same name for 100"
- If there are at least 5 pizzas with same name
- Choose ANY 5 of them and pay 100 total
- Can be used at most once

-----------------------------------------------------------
DISCOUNT 3:
"For every Large pizza, get a free Small of same name"
- For each pair (Large + Small) of same name
- Small becomes free
- Can be used multiple times
- Cannot combine with other discounts

-----------------------------------------------------------
DISCOUNT 4:
"Buy 3 Large pizzas, pay as if they were Medium"
- If total Large pizzas >= 3
- Choose exactly 3 Large pizzas
- Pay Medium price instead of Large
- Can be used at most once

-----------------------------------------------------------
IMPORTANT:
- You can use ONLY ONE discount (or none).
- Return the minimum possible total price.

===========================================================


Input console:
3
margherita 7 8 10   
hawaii 8 9 12       
capricciosa 5 7 13  
4
margherita Small 3  
capricciosa Large 2 
hawaii Large 1      
capricciosa Small 5

Output:
69

*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include<algorithm>

using namespace std;

struct Pizza {
    string name;
    int price_S;
    int price_M;
    int price_L;
};

struct OrderItem {
    string name;
    string size;   // "Small", "Medium", "Large"
    int quantity;
};

struct Counts{
    int s;
    int m;
    int l;
    Counts():s(0),m(0),l(0){};
};

int getPrice(string size, Pizza p){

    if (size == "Small"){
        return p.price_S;
    }
    else if (size == "Medium"){
        return p.price_M;
    }
    else{
        return p.price_L;
    }
};

int  solution(vector<Pizza> &menu, vector<OrderItem> &order) {

    // TODO:
    // 1) Compute base cost (no discount)
    // 2) Compute cost with Discount 1
    // 3) Compute cost with Discount 2
    // 4) Compute cost with Discount 3
    // 5) Compute cost with Discount 4
    // 6) Return minimum of all


    // Αντιστοίχιση όνομα pizzas με τιμές
    unordered_map <string,Pizza> pizza_price;
    for(auto item : menu)
        pizza_price[item.name] = item;

    int base_price = 0;
    int total_pizzas = 0;
    int min_price_pizza = INT_MAX;
    // Συγκέτρωση ποσοτήτων (s, m, l) αν pizza name;
    unordered_map <string, Counts> pizza_counts;
    // Εύρεση τιμής χωρίς κάποια έκπτωση
    int ans;

    for ( auto item : order ){

        int current_price =  getPrice(item.size, pizza_price[item.name]);
        min_price_pizza = min(min_price_pizza, current_price);

        base_price += item.quantity * current_price;

       if (item.size == "Small")
            pizza_counts[item.name].s += item.quantity;
        else if (item.size == "Medium")
            pizza_counts[item.name].m += item.quantity;
        else
            pizza_counts[item.name].l += item.quantity;

        total_pizzas += item.quantity;
    }
    ans = base_price;
    
    // Discount 1
    int dsc1 = base_price;
    if (total_pizzas>=3)
        dsc1 = base_price - min_price_pizza;

    ans = min(ans,dsc1);

    // Discount 2

    int best = INT_MAX;
    for( auto pizza_cnt = pizza_counts.begin(); pizza_cnt != pizza_counts.end(); pizza_cnt++ ){

        int curr_disc =0;
        string name_pizza = pizza_cnt->first;
        Counts  cnts = pizza_cnt ->second;

        int needs = 5;
        if( cnts.s + cnts.m + cnts.l >= 5){
            int needs_l = min(needs, cnts.l); // 5,2
            needs = needs - needs_l;         // 3

            int needs_m = min(needs, cnts.m); // 3,1
            needs = needs - needs_m;         // 2

            int needs_s = min(needs, cnts.s); // 2,2
            needs = needs - needs_s;          // 0
            
            curr_disc = needs_l*pizza_price[name_pizza].price_L
                      +   needs_m*pizza_price[name_pizza].price_M
                      +   needs_s*pizza_price[name_pizza].price_S;
        

            int curr_ans = base_price - curr_disc +100;
            best = min(best,curr_ans);
        }
    }

    ans = min(ans,best);


    // disc3 
    int disc3 = 0;
    for( auto pizza_cnt = pizza_counts.begin(); pizza_cnt != pizza_counts.end(); pizza_cnt++ ){

        string name_pizza = pizza_cnt->first;
        Counts  cnts = pizza_cnt ->second;

        int small_pizzas = min(cnts.l, cnts.s);

        disc3 += small_pizzas*pizza_price[name_pizza].price_S;

    }
    ans = min(ans, base_price - disc3);


    //disc4

    int cnts_L = 0;
    for(auto &cnt : pizza_counts)
        cnts_L = cnts_L + cnt.second.l;
    
    if (cnts_L >= 3){
        // επιλέγουμε 3 Large μονάδες με μέγιστο (price_L - price_M)

        vector<int> top;

        for( auto pizza_cnt = pizza_counts.begin(); pizza_cnt != pizza_counts.end(); pizza_cnt++ ){

            string name_pizza = pizza_cnt->first;
            Counts cnt = pizza_cnt->second;
        
            if ( cnt.l > 0 ){
                // Διάλεξε μαξ 3 από κάθε pizza name
                int large_pizzas = min(3,cnt.l);
                
                for(int i =0;i<large_pizzas; i++)
                    top.push_back(pizza_price[name_pizza].price_L - pizza_price[name_pizza].price_M);   
            }
        }

        sort(top.begin(),top.end(), greater<int>());
        int best_disc = top[0] + top[1] + top[2];

        ans = min(ans, base_price - best_disc);

    }  




    return ans; // replace this
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;  // number of pizzas in menu
    cin >> N;

    vector<Pizza> menu(N);

    for (int i = 0; i < N; i++) {
        cin >> menu[i].name;
        cin >> menu[i].price_S;
        cin >> menu[i].price_M;
        cin >> menu[i].price_L;
    }

    int M;  // number of order items
    cin >> M;

    vector<OrderItem> order(M);

    for (int i = 0; i < M; i++) {
        cin >> order[i].name;
        cin >> order[i].size;
        cin >> order[i].quantity;
    }

    cout << solution(menu, order) << "\n";

    return 0;
}
