package main

import (
	"archive/zip"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

// unzip 함수: zip 파일을 dest 디렉토리에 압축 해제
func unzip(src string, dest string) error {

	r, err := zip.OpenReader(src)
	if err != nil {
		return fmt.Errorf("zip 파일 열기 실패: %w", err)
	}
	defer r.Close()

	for _, f := range r.File {

		fpath := filepath.Join(dest, f.Name)

		// 보안: zip 슬립 공격 방지
		if !strings.HasPrefix(fpath, filepath.Clean(dest)+string(os.PathSeparator)) {
			return fmt.Errorf("zip 슬립 경로 차단됨: %s", fpath)
		}

		if f.FileInfo().IsDir() {

			// 디렉터리인 경우 생성
			if err := os.MkdirAll(fpath, os.ModePerm); err != nil {
				return err
			}
			continue
		}

		// 상위 디렉터리 생성
		if err := os.MkdirAll(filepath.Dir(fpath), os.ModePerm); err != nil {
			return err
		}

		// 파일 생성
		outFile, err := os.OpenFile(fpath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, f.Mode())
		if err != nil {
			return err
		}

		rc, err := f.Open()
		if err != nil {
			outFile.Close()
			return err
		}

		_, err = io.Copy(outFile, rc)

		// 닫기
		outFile.Close()
		rc.Close()

		if err != nil {
			return err
		}
	}
	return nil
}

func main() {

	if len(os.Args) != 3 {
		fmt.Println("사용법: unzip.exe <압축파일경로> <압축해제경로>")
		os.Exit(1)
	}

	zipPath := os.Args[1]
	destPath := os.Args[2]

	fmt.Println("압축 해제 시작...")
	err := unzip(zipPath, destPath)
	if err != nil {
		fmt.Println("압축 해제 실패:", err)
		os.Exit(1)
	}

	fmt.Println("압축 해제 완료:", destPath)
}
