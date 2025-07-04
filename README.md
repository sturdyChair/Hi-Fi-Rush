# DirectX11 모작 팀 포트폴리오 : Hi-Fi-Rush

<img src="https://github.com/sturdyChair/asset/blob/main/HiFi/SSD.gif" width="600" height="400"/>
  
리소스가 포함되어있지 않은 코드 공개용 리포지토리입니다. 정상적으로 동작하지 않을 가능성이 매우 높습니다.

개발 기간 : 2024.09 ~ 2024.11

장르 : 3인칭 리듬 액션 어드벤처

기술 스택:
C, C++, STL, FMOD, Win API, OpenCV, DLL, DirectX 11, vcpkg, HLSL, Effects11, Assimp, ImGui, ImGuizmo, DirectXTK, DirectMath, Nvidia PhysX 5.3 , DLL

역할 : 프레임워커, TA (이펙트, 셰이더)

담당 : 프레임워크, 외부 라이브러리 이식, 카메라, 이펙트 다수, 카트레일 & 터널, 케일 반달레이

제 다른 작업물은 [여기](https://github.com/sturdyChair/portfolio)서 볼 수 있습니다!

---

## 시연 영상 링크 

[Hi-Fi-Rush 전체 프로젝트 영상](https://www.youtube.com/watch?v=rwTkUgP4ITA)

[Hi-Fi-Rush 개인 작업 영상](https://youtu.be/1qcnJ9FaIY8)

---

## 목적 및 설명
포트폴리오 제작, 협업 경험을 위해 개발된 3인칭 리듬 액션 어드벤처 게임 Hi-Fi-Rush의 모작 프로젝트입니다.
상용 엔진을 이용하지 않았으며 DirectX11을 이용해 개발한 엔진을 DLL 프로젝트로 클라이언트 프로젝트에 Export하여 개발했습니다.
제가 담당한 파트는 프레임워크, 외부 라이브러리 이식, 카메라, 이펙트, 카트레일, 케일 반달레이(보스)입니다.

---

## 주요 구현 기능

- [Hi-Fi-Rush 개인 작업 영상](https://youtu.be/1qcnJ9FaIY8) 상단 영상에 상세한 설명 있음

## 1. DirectX 11 기반 렌더링 엔진
### 렌더링

  <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/RenderTarget.jpg" width="600" height="400"/>   
  
- **디퍼드 라이팅**: 연산 부하를 줄이기 위해 G-Buffer 활용   
  - G-Buffer 데이터: `Color`, `Id`, `Position`, `Normal`, `Emissive`.   
    > `Id`버퍼는 픽셀 피킹 등 개발 편의성을 위해 마련됨   
    > G-Buffer 데이터를 이용해 다양한 셰이더 효과를 구현   
- **카툰 렌더링**:    
  - **셀 셰이딩**을 사용한 단계별 음영 처리   
  - **외곽선**을 이용한 강조 효과   
    >Animated 모델: 동일 모델을 2회 Draw하며 정면 컬링과 정점 확장을 이용해 외곽선 구현   
    >Non-Animated 모델: 라플라스 필터와 `Normal`렌더 타겟을 이용, 디퍼드 라이팅 단계에서 외곽선 처리   

---

## 2. 최적화 작업   
### Assimp 라이브러리 활용   
- **FBX 데이터 처리**:   
  - 모델 데이터를 구조체로 선언, 구조체를 **이진 직렬화**하여 파일로 저장   
  - 전처리 과정이 끝난 FBX파일은 더이상 사용하지 않으며 이진화된 파일을 이용   
  - Texture Caching을 통해 동일 텍스쳐의 중복 로딩 방지   
  - 멀티 스레딩을 이용한 병렬 로딩   
- **로딩 시간 단축**:   
  - 결과적으로 30분 이상이었던 로딩 시간을 2분까지 단축   
  - 주로 **이진 직렬화**에서 효과를 봄(30분->5분)   
  - Texture Caching 작업과 함께 불필요하게 공간을 차지하고 있던 데이터 또한 정리, 메모리 사용량을 2GB 가량 절약하고 로딩 시간 또한 기존 5분에서 3분까지 단축시킴   
  - 멀티 스레딩을 이용해 CPU 점유율을 끌어올리고 최종적으로 로딩 시간을 2분까지 단축   
### Object Pooling   
- [**shared_ptr**](#2-스마트-포인터):   
  - shared_ptr의 레퍼런스 관리 기능을 이용해 Pool에 오브젝트를 저장하고 게임 루프에서 회수함 [전체 회수 함수](https://github.com/sturdyChair/asset/blob/main/ObjPool%20Recall.png)   
  - 메모리의 할당, 해제 없이 대량의 객체를 순간적으로 생성할 수 있음    
- **초기화**:   
  - Pool에 배치된 오브젝트는 게임 루프에 포함되거나 게임 루프에서 제거될 때 특수한 Callback 함수를 호출함   
  - Callback 함수는 각 Object에서 직접 구현, 필요한 초기화 작업을 수행함   
### LOD   
- **LOD용 메쉬**:   
  - 메쉬에 디테일 레벨이 다른 정점 버퍼를 할당, 카메라로부터 일정 거리 이상 멀어지면 낮은 디테일 레벨의 메쉬를 사용하도록 구현함   
### Octree   
- **Octree Culling**:   
  - 절두체 컬링을 할 때 사전에 분리해둔 Octree를 기반으로 알고리즘 최적화   
  - 단, 객체 개수가 그리 많지 않아(5000개 이하) Octree 연산 오버헤드가 최적화 효과를 압도하는 경우 발생   
  - 결국 코드에서 제외함   

---

## 3. 충돌 처리   
### PhysX 엔진   
- 지형과 캐릭터의 상호작용, 충돌 관리   
- **메쉬 콜라이더**:  
  - 메쉬와 동일한 모양의 충돌체, 주로 지형에 사용됨  
  - PhysX 엔진에 메쉬의 정점 정보를 전달해 만들어짐  
- [**Character Controller(CCT)**](#5-캐릭터-컨트롤러):  
  - 캡슐 모양의 충돌체  
  - PhysX로 구성된 지형과 상호작용하기 위해 **움직이는 객체**가 가지고 있는 Component 객체  
  - 주로 플레이어, 몬스터 AI등이 소유하고 있으며 이동을 제어함  
### Collision Manager  
- 전투, 상호작용, 이벤트 처리 등 게임 로직에 필요한 충돌 처리를 담당하는 객체  
- 충돌 처리가 필요한 객체는 Collider Component를 소유, 매 프레임 Collider를 Collision Manager에 등록함  
- 등록되지 않은 Collider는 유효하지 않은 것으로 판별, 그 프레임에서 충돌 처리를 하지 않음  
- Collider는 Collision Group으로 나뉘며 그룹 기반으로 충돌 검사 시행  
- 각 Collider가 가지고 있는 고유 ID를 이용해 각 Collider 쌍의 충돌 상태를 저장함   
  > <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/Collision.jpg" width="600" height="400"/>   
  >
---

## 4. 이펙트 프레임워크  
### Effect Manager  
- **객체 관리**:  
  - State를 이용한 LifeCycle 관리, 재생 속도 조절  
  - 오브젝트 풀링을 이용, 메모리 할당과 해제 없이 이펙트 객체 재사용  
  - `Union Effect`로 여러 이펙트를 통합 및 관리  
    >
    > ![img](https://github.com/sturdyChair/asset/blob/main/EffectBase1.png)  
    >  
    > 이펙트 인터페이스, 수명 관리를 위한 Enum과 콜백 함수가 정의되어있음  
    >
    > <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/UnionEffect.jpg" width="600" height="400"/>  
    > 
- **툴 지원**:  
  - ImGui 및 Imguizmo 라이브러리를 사용한 편집 기능 제공
    > <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/EffectTool.jpg" width="600" height="400"/>    
  - UV좌표, 컬러, 재생률, 수명, 크기 등 다양한 정보를 수정 및 확인 가능  
### Screen Space Decal   
- Decal Box가 그려질 픽셀에 대해 World → Local 공간 변환, G-Buffer의 정보를 이용해 내부에만 Decal 적용
  > <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/SSD_Decal.jpg" width="600" height="400"/>
  >
  > <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/SSD.gif" width="600" height="400"/>   
  > SSD를 이용한 스포트라이트 연출, 레벨의 모든 라이트를 제어하는 대신 SSD를 이용해 '빛'이 비추는 공간만 특수하게 처리함
### 파티클    
- **Point Instancing**:    
  - 각 Point의 생성 범위와 Pivot을 설정해 다양한 효과 연출 가능    
 
---

## 5. 보스 AI & 연출   
### 케일 반달레이 보스전   
- **이펙트 & 사운드**:   
  - 모델 애니메이션의 연동으로 키프레임 기반 VFX, SFX 관리
    >  <img src="https://github.com/sturdyChair/asset/blob/main/HiFi/JC_Effect.gif" width="600" height="400"/>   
    >
- **4단계 페이즈**:   
  - 특정 캐릭터와 상호작용 및 약점 공략 가능   
  - 페이즈 변경에 따른 이벤트 처리, 특수 연출   
  - 페이즈에 따라 BGM 변경, 리듬 처리 초기화   
- **AI 설계**:   
  - 패턴에 기반한 거리 조절 AI   
  - 루트 애니메이션 기반 이동 로직   
  - 슈퍼아머 게이지와 그로기 상태 구현   
### 연출  
- **Screen Space Reflection, Cubemap Reflection**:  
  - G-Buffer 데이터를 활용해 반사 구현, 매끈한 제질의 바닥 연출  
- **Rhythm Parry**:  
  - 모델의 특정 Bone과 카메라 행렬을 동기화해 역동적인 카메라 연출  
  - 음악의 리듬에 맞춰 공격을 방어하는 것에 성공해야 다음 페이즈로 넘어가도록 설계  
- **Cinematic**:  
  - 페이즈 변경에 따라 인게임 시네마틱을 재생하도록 구현  
 
---

## 6. 카메라 ([트러블 슈팅](#4-카메라-제어))  
- **View 행렬**:  
  - Yaw, Pitch, Roll 각도로 Look Vector 정의  
  - Target의 좌표를 기준으로 Distance, Offset을 이용해 위치 계산  
  - 위의 두 정보를 이용해 View 행렬 계산  
  - 위에 설명된 변수들은 목표 값을 따로 가지고 있으며 시간에 따라 부드럽게 목표 값에 가까워짐  
- **컨트롤**:  
  - 평소에는 플레이어 등 카메라를 점유한 객체를 바라보며 일정 거리를 유지, 마우스에 움직임에 따라 각도 조절  
  - 전투 돌입시 가장 가까운 적을 향해 자동 록온, 마우스 이동량을 감지해 임계값 이상일 경우 록온을 해제하게 구현  
  - 특정 이벤트가 일어나면 주어진 행렬을 따라다니며 입력을 무시함  
  - 맵의 특정 구간에 도달하면 카메라가 고정되며 플레이어의 움직임도 특정 축에 맞게 고정됨  

---

## 7. 카트레일 & 터널  
### 터널  
- **터널 구성**:  
  - Instancing을 이용해 터널 매쉬 400개를 길게 배치  
  - 터널의 끝 부분은 Deffered Lighting 단계에서 안개 효과를 적용해 처리  

### 카트레일 애니메이션  
- [애니메이션 분리 제어](#3-애니메이션-분리제어):  
  - Bone을 태그에 따라 특정 그룹들로 분리, 서로 다른 애니메이션을 동시에 재생할 수 있도록 함  
  - 4개의 바퀴와 브레이크가 서로 독립적으로 상태를 제어할 수 있게됨  
 
---

## 트러블슈팅

### 1. PhysX 엔진  
프로젝트 초기에 가장 말썽을 부렸던 것이 PhysX 엔진이었습니다.

이전에 [개인으로 진행한 프로젝트](https://github.com/sturdyChair/BPM)에서 PhysX를 사용했을 때도 라이브러리를 빌드하고 프로젝트에 포함시키는 과정에서 상당히 고생을 했지만, 이번에는 그 때 만들어둔 기능을 거의 그대로 사용할 수 있으리라 기대했습니다.

하지만 PhysX 객체와 저희 클라이언트에서 렌더링되는 물체의 좌표와 형태가 어긋나는 일이 계속해서 발생했습니다.
 
저는 그 원인을 알아내기 위해 PhysX Visual Debugger를 코드에 포함해 PhysX 객체를 시각화했고, 대부분의 물체가 본래의 형태를 알아볼 수 없게 망가져있는 것을 확인할 수 있었습니다.

다만 회전이 적용되지 않은 물체는 위치와 형태가 정상적이었습니다.

저는 이 시점에서 '좌표계 간 행렬 변환에 문제가 버그의 원인일 것' 이라는 추측을 했고 포럼에서 PhysX, Unreal, DirectX의 좌표계 간 차이에 대해 검색한 결과 행렬을 전치해주지 않아서 버그가 일어난 것임을 알게되었습니다.

실제로 PhsyX 객체를 만드는 과정에서 물체가 가진 행렬을 전치해 전달해주는 것으로 버그는 해결되었습니다.

### 2. 스마트 포인터
이전 프로젝트에서 사용한 프레임워크를 옮겨오는 과정에서 저는 당시 가장 불편했던 점이 무엇이었는지 고민했습니다.

당시 저는 레퍼런스 카운터를 수동으로 체크해주며 객체의 수명을 관리하고 있었습니다.

그러나 협업을 하게 되면 실수의 가능성도 커지고, 관리를 위해 코딩 규칙을 만드는 것 보다는 원천적으로 실수가 일어나기 어려운 프레임워크를 제공해주는 것이 저의 역할이라고 생각했습니다.

그래서 STL의 shared_ptr을 이용해 자동으로 포인터의 수명이 관리되도록 처음부터 프레임워크를 작성하고, 협업자들 또한 shared_ptr을 사용하기 쉽도록 매크로를 제공했습니다.

스마트 포인터를 이용한 프레임 워크는 프로젝트 초기, 몇번 있었던 순환 참조 문제를 제외하면 메모리 문제를 전혀 일으키지 않았고 이 덕분에 저희는 더 생산성 있는 일에 집중할 수 있었습니다.

>
> ![img](https://github.com/sturdyChair/asset/blob/main/MakeSharedEnabler%20Macro.png)
>
> private 생성자를 가진 객체에 make_shared 함수를 사용하기 위한 Wrapper 객체 선언 매크로
>

>
> ![img](https://github.com/sturdyChair/asset/blob/main/MakeSharedEnabler%20Creator.png)
>
> 위 매크로를 이용한 예시
>

### 3. 애니메이션 분리제어
카트레일 모델을 처음 확인했을 때 상당히 곤란한 상황이었습니다.
카트레일 몸체, 4개의 바퀴, 브레이크, 그리고 경고등까지 하나의 모델로 묶여있었지만, 로직에 맞게 서로 다른 애니메이션을 재생해줘야했기 때문입니다.
그러나 기존에 사용하던 애니메이션 제어 방식으로는 하나의 모델을 두 그룹으로 분리해 작동시키는 것이 한계였습니다.

우선 기존의 애니메이션 분리 제어 방식을 일반화하고 확장하는 것에서 시작했습니다.

Bone을 분리시키고, 그 그룹에 문자열로 된 Key 값을 붙혀주어 나중에 접근이 용이하도록 설계했습니다. 이 Key는 STL의 map을 사용해 저장했습니다.
그리고 분리된 Bone 그룹마다 현제 재생 중인 애니메이션, 키프레임, 반복 여부 등을 저장했고, 애니메이션의 중복 재생을 피하기 위해 매 프레임 이미 재생된 애니메이션을 체크했습니다.

Bone의 분리는 Bone 그룹의 최상위 부모로부터 재귀적으로 같은 그룹에 포함시키는 방식으로 구현했습니다.

결과적으로 4개의 바퀴와 브레이크에 서로 다른 상태를 부여하고, 독립적으로 제어하며, 그 상태를 애니메이션을 통해 표현할 수 있었습니다.

>
> ![img](https://github.com/sturdyChair/asset/blob/main/Split%20Animation.png)
>
> 애니메이션 분리제어용 함수와 변수
>

>
> ![img](https://github.com/sturdyChair/asset/blob/main/Split%20Anim%20Recursion.png)
>
> 하나의 Bone을 그룹에 등록하면 그 하위의 자식 Bone들이 모두 같은 그룹에 등록된다
>

### 4. 카메라 제어
이 코드에선 View Matrix를 정의할 때 3개의 각도를 담은 벡터, LookAt, Distance의 3가지 정보를 통해 매 프레임 계산하도록 설계했습니다.
처음에는 이 값들에 목표값이 없었기 때문에 마우스 이동에 즉시 반응해서 회전했고 큰 문제는 없었습니다.

하지만 3D 액션 게임에선 필수인 록온 시스템을 구현할 때 문제가 생겼습니다.
목표에 맞춰 카메라가 즉시 회전하며 화면이 부자연스러워진 것이었습니다.
그래서 저는 이 값들에 목표 값을 두고, 그 목표 값은 즉시 변화시키되 실제 View Matrix를 정의하는 변수들을 시간에 따라 점점 목표치에 가까워지게 구현해 문제를 해결했습니다.

>
> ![img](https://github.com/sturdyChair/asset/blob/main/Cam%20Interpol.png)
>
> 보간 구현 [Line 343](https://github.com/sturdyChair/Hi-Fi-Rush/blob/master/Client/Private/Player_Camera.cpp)
>

>
> ![img](https://github.com/sturdyChair/asset/blob/main/Cam%20LockOn.png)
>
> 록온 구현, 각도가 2PI를 넘은 상태에서 록온을 하면 회전 속도가 지나치게 빠른 버그가 있어 임계치를 정해둠
>

카메라에는 또 하나 중요한 기능이 있었는데, 바로 특수 연출을 위해 카메라를 모델의 특정한 Bone Matrix와 동기화시키는 것이었습니다.
처음 이 기능을 구현했을 때 여러 문제가 있었습니다.

첫번째는 Far Plane이 지나치게 가까워져 잘려선 안될 부분이 잘려나가 그려지는 문제였습니다.
이 문제는 단순히 Matrix의 크기가 너무 작은 것이 원인이어서 Matrix를 정규화해주는 것으로 해결되었습니다.

두번째는 진입, 탈출의 부자연스러움이었습니다.
Bone Matrix와의 동기화가 시작되고 끝날 때 카메라가 순간이동을 하며 부자연스럽게 움직였기 때문입니다.
이를 해결하기 위해 저는 카메라가 Bone과 동기화를 시작하거나 끝낸 순간을 기록, 이전의 Matrix를 보존하고 현제 카메라가 가져야할 Matrix와 선형보간을 하는 방식으로 해결했습니다.

### 5. 캐릭터 컨트롤러
PhysX를 기반으로 지형을 구현했기 때문에 플레이어 객체 담당자와 AI 담당자에게는 PhysX 지형과 상호작용 가능한 기능을 제공해야했습니다.
저는 이 문제에 대해 다각도로 고민해보았습니다.

우선 PhysX를 잘 모르는 사람도 사용할 수 있어야했습니다. 그래서 기능을 한번 캡슐화할 필요가 있다고 생각했고 컴포넌트 객체로 제공하는 것이 가장 알맞을 것이라 생각했습니다.

다음으로 작은 계단이나 경사로를 오르내릴 수 있어야했습니다. PhysX를 이용해 메쉬의 모습 그대로 지형을 만들어 크고 작은 굴곡을 많았기 때문입니다.
다행히도 PhysX가 제공하는 Character Controller 객체가 이런 기능을 지원하고 있었습니다.

마지막으로 가속, 중력 등 물리적인 처리를 지원하되 지나치게 현실적이지는 않아야했습니다. 게임 속 캐릭터의 움직임은 조작감과 연출을 위해 비현실적인 모습을 보여주기 때문입니다.
그래서 저는 객체 설계에 가속도, 중력, 속력, 힘을 이용한 유사 물리 처리 기능을 지원하기로 했습니다.

위의 고려사항들에 대해 고민한 결과 저는 PhysX Character Controller를 Wrapping한 컴포넌트 객체 CCT를 설계해 팀원들에게 제공했습니다.
CCT를 제공받은 팀원은 실제 PhysX 객체에 대한 이해 없이도 쉽게 지형과 상호작용 가능한 캐릭터를 만들 수 있었으며 이동 같은 기본적인 액션 뿐 아니라 점프, 와이어 액션, 넉백 등 다양한 액션을 쉽게 구현할 수 있었습니다.
>
> ![img](https://github.com/sturdyChair/asset/blob/main/CCT%20Function%20Move.png)
>
> 무브먼트 함수를 통해 PhysX 객체를 몰라도 이동 구현이 가능
>

>
> ![img](https://github.com/sturdyChair/asset/blob/main/CCT%20Function%20Physics.png)
>
> 유사 물리 기능 지원으로 다양한 액션 구현
>

>
> ![img](https://github.com/sturdyChair/asset/blob/main/CCT%20Update.png)
>
> PhysX와의 상호작용은 구현 내부에 숨김
> [Line 202](https://github.com/sturdyChair/Hi-Fi-Rush/blob/master/Engine/Private/CharacterController.cpp)
> 

### 6. 리듬 연동 시스템
게임 자체가 리듬 액션 게임이다보니 진행이 음악의 리듬에 맞도록 구현해야만했습니다.
로직을 음악에 연동시키기 위해서는 코드 전체가 단 하나의 음악과 그 리듬에 대한 정보를 알 수 있도록 해야했고 그래서 저는 Beat Manager라는 객체를 싱글턴으로 설계했습니다.

Beat Manager에는 박자의 길이, 박자가 변하는 순간, 누적 박자 등 다양한 정보가 저장되어있고 이에 접근할 수 있는 함수가 정의되어있습니다.
또 리듬 초기화, 음악과 리듬 연동, 자동 음악 시퀀스 재생 등 다양한 기능을 지원해 여러 음원 파일로 나누어진 배경음악에 대해서도 대응할 수 있습니다.

이런 설계를 바탕으로 저를 포함한 팀원들이 리듬에 맞추어 코드를 제어하는 구현을 해낼 수 있었습니다.


