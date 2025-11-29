import { useEffect, useState } from 'react';
import type { ErrorResponse } from '@/types';

interface ErrorNotificationProps {
  error: ErrorResponse | null;
  onClose: () => void;
  autoHideDuration?: number;
}

export const ErrorNotification = ({
  error,
  onClose,
  autoHideDuration = 3000,
}: ErrorNotificationProps) => {
  const [isVisible, setIsVisible] = useState(false);

  useEffect(() => {
    if (error) {
      setTimeout(() => setIsVisible(true), 10);
      
      const timer = setTimeout(() => {
        setIsVisible(false);
        setTimeout(onClose, 500);
      }, autoHideDuration);

      return () => clearTimeout(timer);
    }
  }, [error, autoHideDuration, onClose]);

  const handleClose = () => {
    setIsVisible(false);
    setTimeout(onClose, 500);
  };

  if (!error) return null;

  return (
    <div className="fixed top-0 left-0 right-0 z-50 flex justify-center">
      <div
        className={`w-full max-w-md bg-red-50 border border-red-200 text-red-800 px-6 py-4 rounded-b-lg shadow-lg transform transition-transform duration-500 ${
          isVisible ? 'translate-y-0' : '-translate-y-full'
        }`}
      >
        <div className="flex justify-between items-start">
          <div>
            <h3 className="font-semibold">Erreur {error.code}</h3>
            <p className="mt-1 text-sm">{error.error}</p>
          </div>
          <button
            onClick={handleClose}
            className="text-red-400 hover:text-red-600 transition-colors duration-200 ml-4"
          >
            <svg className="w-5 h-5" fill="currentColor" viewBox="0 0 20 20">
              <path
                fillRule="evenodd"
                d="M4.293 4.293a1 1 0 011.414 0L10 8.586l4.293-4.293a1 1 0 111.414 1.414L11.414 10l4.293 4.293a1 1 0 01-1.414 1.414L10 11.414l-4.293 4.293a1 1 0 01-1.414-1.414L8.586 10 4.293 5.707a1 1 0 010-1.414z"
                clipRule="evenodd"
              />
            </svg>
          </button>
        </div>
      </div>
    </div>
  );
};