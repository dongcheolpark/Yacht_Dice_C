#include "scoreboard.hpp"
scoreboard::scoreboard() {
	up.resize(6);
	for(int i = 0;i<6;i++) {
		up[i] = -1;
	}
	bonus = false;
	down.resize(6);
	for(int i = 0;i<6;i++) {
		down[i] = -1;
	}
}

void scoreboard::setValue(int i,int val) {
	if(0 <= i && i <= 5) {
		setUp(i,val);
	}
	else if(7<=i && i <= 12) {
		setDown(i-7,val);
	}
}

void scoreboard::setscore() {
	for(auto item : up) {
		if(item == -1) score += 0;
		else score += item;
	}
	for(auto item: down) {
		if(item == -1) score += 0;
		else score += item;
	}
	score += 35*(int)bonus;
}

void scoreboard::setUp(int i,int val) {
	if(val > (i+1)*6 || val < 0) return;
	up[i] = val;
}
void scoreboard::setDown(int i,int val) {
	down[i] = val;
}

std::string scoreboard::tostring()  {
	std::string res;
	for(auto item : up) {
		res.append(ydc::format_string("%d ",item));
	}
	res.append(ydc::format_string("%d ", bonus ? 0 : 35));
	for(auto item : down) {
		res.append(ydc::format_string("%d ",item));
	}
	return res;
}

int scoreboard::getUp(int n) {
	return up[n];
}

int scoreboard::getDown(int n) {
	return down[n];
}

int scoreboard::getBonus() {
	return bonus ? 35 : 0;
}

int scoreboard::getscore() {
	setscore();
	return score;
}

std::vector<int> scoreboard::calculate(dice_game dice) { //화면에 띄워질 때 어떤 값을 보여줄지를 처리해줌
	std::vector<int> res(14);
	int sum[6] = {0,};
	for(int i = 0;i<5;i++) {
		sum[dice.get_dices(i)-1]++;
	}
	for(int index = 0;index<6;index++) {
		if(index >= 0 && index <= 5) {
			for(int i = 0;i<5;i++) {
				if(dice.get_dices(i) == index+1) {
					res[index] += index+1;
				}
			}
		}
	}//up 계산
	res[6] = getBonus();//보너스 표시
	for(int i = 0;i<5;i++) res[7] += dice.get_dices(i);// 초이스
	int max_straight = 0;
	int straight = 0;
	bool three = false,two = false;
	for(int i = 0;i<6;i++) {
		if(sum[i] == 0) {
			max_straight = (straight > max_straight) ? straight : max_straight ;
			straight = 0;
		}
		else {
			straight++;
			if(sum[i] == 2) two = true;
			if(sum[i] == 3) three = true;
			if(sum[i] >= 4) res[8] = res[7];//포카인드
			if(sum[i] == 5) res[12] = 50; // 야추
		}
	}
	max_straight = (straight > max_straight) ? straight : max_straight ;
	if(max_straight >= 4) {
		res[10] = 15;//스몰스트레이트
	}
	if(max_straight == 5) {
		res[11] = 30; //라지스트레이트
	}
	if(two&&three) res[9] = res[7];//풀하우스
	return res;

}

std::vector<int> scoreboard::display(dice_game dice) {
	auto res = calculate(dice);
	for(int i = 0;i<6;i++) {
		if(up[i] != -1) res[i] = up[i];
	}
	for(int i = 0;i<6;i++) {
		if(down[i] != -1) res[i+7] = down[i];
	}
	res[13] = getscore();
	return res;
}

int scoreboard::isScoreLock() {
	int res = 0;
	for(int i = 0;i<6;i++) {
		res |= up[i] != -1 ? 1 : 0;
		res <<= 1;
	}
	res <<= 1;
	for(int i = 0;i<6;i++) {
		res |= down[i] != -1 ? 1 : 0 ;
		res <<= 1;
	}
	res >>= 1;
	return res;
}