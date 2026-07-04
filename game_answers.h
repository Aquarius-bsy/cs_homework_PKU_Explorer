#ifndef GAME_ANSWERS_H
#define GAME_ANSWERS_H

// 集中配置各地点（1~12）、旧日之境小店店名、禁书收藏馆索号、酒馆花神庙碑问答、吟游剧场《踏秋图》作者问答的答案。
// 请只修改 game_answers.cpp 中的 configureGameAnswers()。
//
// 运行时也可调用 SiteAnswerBook::instance()：
//   setAnswer(siteId, "单一答案");
//   setAcceptedAnswers(siteId, {"可接受答案1", "可接受答案2"});
void configureGameAnswers();

#endif // GAME_ANSWERS_H
