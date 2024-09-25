;; https://lists.defectivebydesign.org/archive/html/emms-help/2019-01/msg00023.html
;; change Windows volume using AutoHotKey script WinVol
(defcustom emms-winvol-program "WinVol.exe"
  "Name, and possibly location, of the WinVol executable"
  :group 'emms-volume
  :type 'string)

;;;###autoload
(defun emms-volume-winvol-change (amount)
  "Change Windows volume by AMOUNT by using WinVol."
  (if (> amount 0)
      (setq amount (concat "+" (number-to-string amount)))
    (setq amount (number-to-string amount)))
  (message "Current playback: %s"
	   (with-temp-buffer
	     (when (zerop (shell-command (concat (expand-file-name emms-winvol-program)
						 " " amount)
					 (current-buffer)))
	       (if (progn (goto-char (point-min))
			  (re-search-forward "[0-9]+%" nil t))
		   (match-string 0))))))

(provide 'emms-volume-winvol)

;;; emms-volume-winvol.el ends here
