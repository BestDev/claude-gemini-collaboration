# Code Generator 프로젝트 개요

## 1. 프로젝트명
- Code Generator

## 2. 목표
- 사용자의 요구사항 명세(자연어)를 입력받아, 특정 프로그래밍 언어의 소스 코드를 자동으로 생성하는 AI 에이전트 개발.
- 초기 버전은 Python 코드 생성을 목표로 함.

## 3. 주요 기능
- 자연어 처리(NLP)를 통한 요구사항 분석
- 분석된 요구사항을 코드 구조로 변환
- 코드 생성 및 유효성 검사
- 생성된 코드 파일로 저장

## 4. 초기 기술 스택 구상
- **언어**: Python
- **핵심 라이브러리**: 
    - AI/ML: Pytorch 또는 Tensorflow/Keras
    - NLP: Hugging Face Transformers
- **프레임워크**: 필요시 FastAPI를 사용하여 API 형태로 제공하는 것을 고려
