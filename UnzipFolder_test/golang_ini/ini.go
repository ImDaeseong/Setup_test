package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Println("사용법: create_ini.exe <설치경로>")
		os.Exit(1)
	}

	basePath := os.Args[1]

	iniPath := filepath.ToSlash(filepath.Join(basePath, "MariaDB", "data", "my.ini"))
	basedir := filepath.ToSlash(filepath.Join(basePath, "MariaDB"))
	datadir := filepath.ToSlash(filepath.Join(basePath, "MariaDB", "data"))
	plugindir := filepath.ToSlash(filepath.Join(basePath, "MariaDB", "lib", "plugin"))

	// my.ini 내용
	content := fmt.Sprintf(
		`[mysqld]
basedir=%s
datadir=%s
port=23306
innodb_buffer_pool_size=2048M
character-set-server=utf8mb4
collation-server=utf8mb4_general_ci

[client]
port=23306
plugin-dir=%s
`, basedir, datadir, plugindir)

	// CRLF로 변환
	content = strings.ReplaceAll(content, "\n", "\r\n")

	// my.ini 작성
	err := os.WriteFile(iniPath, []byte(content), 0644)
	if err != nil {
		fmt.Println("INI 파일 작성 실패:", err)
		os.Exit(1)
	}

	fmt.Println("INI 파일 작성 완료:", iniPath)
}
