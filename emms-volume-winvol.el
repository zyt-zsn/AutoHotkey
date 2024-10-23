;; https://lists.defectivebydesign.org/archive/html/emms-help/2019-01/msg00023.html
;; change Windows volume using AutoHotKey script WinVol
(defcustom emms-winvol-program
  (let ((executable (if (eq system-type 'windows-nt)
                        "WinVol.exe" "WinVol"))
        (default-directory
         (or (and load-file-name
                  (file-name-directory load-file-name))
             default-directory)))
    (cl-labels ((try-directory (directory)
                  (and (file-directory-p directory)
                       (file-executable-p (expand-file-name executable directory))
                       (expand-file-name executable directory))))
      (or (executable-find executable)
          ;; This works if epdfinfo is in the same place as emacs and
          ;; the editor was started with an absolute path, i.e. it is
          ;; meant for Windows/Msys2.
          (and (stringp (car-safe command-line-args))
               (file-name-directory (car command-line-args))
               (try-directory
                (file-name-directory (car command-line-args))))
          ;; If we are running directly from the git repo.
          (try-directory (expand-file-name "../server"))
          ;; Fall back to epdfinfo in the directory of this file.
          (expand-file-name executable))))
  "Name, and possibly location, of the WinVol executable"
  :group 'emms-volume
  :type 'file)

;;;###autoload
(defun emms-volume-winvol-change (amount)
  "Change Windows volume by AMOUNT by using WinVol."
  (if (> amount 0)
      (setq amount (concat "+" (number-to-string amount)))
    (setq amount (number-to-string amount)))
  (message "Current playback: %s"
		   (with-temp-buffer
			 (progn (zerop (shell-command (concat emms-winvol-program
												  " " amount)
										  (current-buffer)))
					(if (progn (goto-char (point-min))
							   (re-search-forward "[0-9]+%" nil t))
						(match-string 0))))))

(setq emms-volume-change-function #'emms-volume-winvol-change)

(provide 'emms-volume-winvol)

;;; emms-volume-winvol.el ends here
