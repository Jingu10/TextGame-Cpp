# ⚔️ C++ Console Text RPG

콘솔 환경에서 구동되는 객체지향 기반의 턴제 텍스트 RPG입니다. 
단순한 절차지향적 스파게티 코드를 탈피하고, **디자인 패턴(State, MVC)과 SOLID 원칙**을 적용하여 유지보수와 확장이 용이한 아키텍처를 설계하는 데 집중한 프로젝트입니다.

## 🌟 핵심 기능 (Features)

* **상태 패턴(State Pattern) 기반의 씬(Scene) 제어**
  * 마을, 상점, 퀘스트 길드, 던전 등 각 화면을 독립된 객체로 분리하여 `GameManager`의 거대한 분기문을 제거했습니다.
* **독립적인 매니저(Manager) 시스템**
  * `BattleManager`, `QuestManager`를 통해 도메인 데이터(캐릭터, 몬스터)와 화면 출력(UI) 사이의 비즈니스 로직을 완벽히 분리했습니다.
* **메모리 누수 없는 인벤토리 시스템**
  * `std::shared_ptr`를 활용하여 인벤토리와 장착 슬롯 간의 아이템 소유권을 안전하게 공유하고 동기화합니다.
* **역동적인 텍스트 연출**
  * `<thread>`와 `<chrono>`를 이용한 출력 딜레이 연출과 점자 유니코드 기반의 고퀄리티 ASCII Art로 콘솔 텍스트 게임 특유의 타격감과 몰입감을 극대화했습니다.
* **퀘스트 시스템**
  * 몬스터 처치, 스킬 사용, 던전 클리어 등 다양한 조건의 퀘스트를 수락하고 진행도를 추적하여 보상을 수령할 수 있습니다.

## 🏗️ 아키텍처 설계 (Architecture)

프로젝트는 역할과 책임에 따라 5개의 주요 계층으로 분리되어 있습니다.

1. **Domain (Data):** `Character`, `Monster`, `Item`, `Quest` - 순수 데이터와 상태 변경 메서드만 포함.
2. **Policy (Rules):** `Policy` - 데미지 공식, 속성 상성, 드롭 테이블 등 무상태(Stateless) 비즈니스 규칙.
3. **View (UI):** `ConsoleUI` - 콘솔 입출력, ASCII Art, 딜레이 연출을 전담하는 유일한 클래스.
4. **Controller (Manager):** `BattleManager`, `QuestManager` - 데이터와 뷰 사이의 흐름을 중재.
5. **State (Scene):** `Scene` 인터페이스를 상속받은 각 장소 객체들로 메인 루프 라우팅 처리.

## 🛠️ 기술 스택 (Tech Stack)
* **Language:** C++ (C++11 이상)
* **Standard Library:** `std::vector`, `std::set`, `std::shared_ptr`, `<thread>`, `<chrono>`
* **Environment:** Visual Studio / Windows Console (UTF-8 인코딩 적용)

## 🚀 실행 방법 (How to Run)
1. 저장소를 클론합니다.
   ```bash
   git clone [https://github.com/Jingu10/TextGame-C-.git](https://github.com/Jingu10/TextGame-C-.git)
   
2. Visual Studio에서 .sln 파일을 열거나, C++ 컴파일러를 이용해 main.cpp를 포함한 모든 소스 파일을 빌드합니다.

3. 생성된 실행 파일(.exe)을 실행하여 게임을 플레이합니다!
