;;; buffer-flip-autoloads.el --- automatically extracted autoloads  -*- lexical-binding: t -*-
;;
;;; Code:

(add-to-list 'load-path (directory-file-name
                         (or (file-name-directory #$) (car load-path))))


;;;### (autoloads nil "buffer-flip" "buffer-flip.el" (0 0 0 0))
;;; Generated autoloads from buffer-flip.el

(autoload 'buffer-flip "buffer-flip" "\
Begin cycling through buffers.
With prefix ARG, invoke `buffer-flip-other-window'.
ORIGINAL-CONFIGURATION is used internally by
`buffer-flip-other-window' to specify the window configuration to
be restored upon abort.

\(fn &optional ARG ORIGINAL-CONFIGURATION)" t nil)

(autoload 'buffer-flip-other-window "buffer-flip" "\
Switch to another window and begin cycling through buffers in that window.
If there is no other window, one is created first." t nil)

(register-definition-prefixes "buffer-flip" '("buffer-flip-"))

;;;***

;;;### (autoloads nil nil ("buffer-flip-pkg.el") (0 0 0 0))

;;;***

;; Local Variables:
;; version-control: never
;; no-byte-compile: t
;; no-update-autoloads: t
;; coding: utf-8
;; End:
;;; buffer-flip-autoloads.el ends here
