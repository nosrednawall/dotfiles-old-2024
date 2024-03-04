;;; init.el --- Some summary -*- lexical-binding: t -*-

;; Author: Anderson
;; Maintainer: Anderson
;; Version: version
;; Package-Requires: (dependencies)
;; Homepage: homepage
;; Keywords: keywords


;; This file is not part of GNU Emacs

;; This file is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; For a full copy of the GNU General Public License
;; see <http://www.gnu.org/licenses/>.


;;; Commentary:

;; My commentary

;;; Code:
;;; init.el --- Initialization file for Emacs
;;; Commentary: Emacs Startup File --- initialization for Emacs
;; Adiciona o repositório MELPA
;;; code:

;; Don't show the warnings buffer just because some package has used a
;; deprecated API
(setq warning-minimum-level :error)

(require 'package)
(setq package-enable-at-startup nil)
(add-to-list 'package-archives
		 '("melpa" . "https://melpa.org/packages/") t)

;;(setq package-archives '(("melpa" . "http://melpa.org/packages/")
;;                         ("gnu" . "http://elpa.gnu.org/packages/")
;;                         ("nongnu" . "https://elpa.nongnu.org/nongnu/"))
;;      gnutls-algorithm-priority "NORMAL:-VERS-TLS1.3"
;;      use-package-always-ensure t)


(package-initialize)

;; Bootstrap use-package
(unless (package-installed-p 'use-package)
  (package-refresh-contents)
  (package-install 'use-package))


;; Carrega os pacotes que estão no arquivo ORG - Não uso mais
(org-babel-load-file (expand-file-name "~/.emacs.d/emacs.org"))
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages
   '(web-mode ggtags yasnippet auto-complete org-bullets neotree all-the-icons centaur-tabs buffer-flip which-key gruvbox-theme use-package smex magit eglot dap-mode counsel try projectile dashboard autothemer)))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
