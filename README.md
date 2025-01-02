# DirectX11 모작 팀 포트폴리오 : Hi-Fi-Rush
TODO : 여기에 타이틀 이미지 삽입

리소스가 포함되어있지 않은 코드 공개용 리포지토리입니다. 정상적으로 동작하지 않을 가능성이 매우 높습니다.

개발 기간 : 2024.09 ~ 2024.11

장르 : 3인칭 리듬 액션 어드벤처

기술 스택:
C, C++, STL, FMOD, Win API, OpenCV, DLL, DirectX 11, vcpkg, HLSL, Effects11, Assimp, ImGui, ImGuizmo, DirectXTK, DirectMath, Nvidia PhysX 5.3 , DLL

역할 : 프레임워커, TA (이펙트, 셰이더)

담당 : 프레임워크, 외부 라이브러리 이식, 카메라, 이펙트 다수, L.I.F.T, 케일 반달레이

---

## 시연 영상 링크 

[Hi-Fi-Rush 전체 프로젝트 영상](https://www.youtube.com/watch?v=rwTkUgP4ITA)

[Hi-Fi-Rush 개인 작업 영상](https://youtu.be/1qcnJ9FaIY8)

---

## 목적 및 설명
포트폴리오 제작, 협업 경험을 위해 개발된 3인칭 리듬 액션 어드벤처 게임 Hi-Fi-Rush의 모작 프로젝트입니다.
상용 엔진을 이용하지 않았으며 DirectX11을 이용해 개발한 엔진을 DLL 프로젝트로 클라이언트 프로젝트에 Export하여 개발했습니다.
제가 담당한 파트는 프레임워크, 외부 라이브러리 이식, 카메라, 이펙트, L.I.F.T(터널 맵), 케일 반달레이(보스)입니다.

---

## 주요 구현 기능

- [Hi-Fi-Rush 개인 작업 영상](https://youtu.be/1qcnJ9FaIY8) 상단 영상에 상세한 설명 있음

## 1. DirectX 11 기반 렌더링 엔진
### 렌더링
- **디퍼드 라이팅**: 연산 부하를 줄이기 위해 G-Buffer 활용
  - G-Buffer 데이터: `Color`, `Id`, `Position`, `Normal`, `Emissive`.
- **카툰 렌더링**: 
  - **셀 셰이딩**을 사용한 단계별 음영 처리
  - **외곽선**을 이용한 강조 효과
    >Animated 모델: 동일 모델을 2회 Draw하며 정면 컬링과 정점 확장을 이용해 외곽선 구현
    >
    >Non-Animated 모델: 라플라스 필터로 외곽선 처리

---

